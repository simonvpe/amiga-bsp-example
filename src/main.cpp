#include "a500.hpp"
#include "drivers/mouse.hpp"
#include "copper.hpp"
#include "sprites/starfield.hpp"

#include <array>

constexpr auto BPL1PTH = bsp.chipset[Chipset::Register::BPL1PTH];
constexpr auto SPR0PTH = bsp.chipset[Chipset::Register::SPR0PTH];
constexpr auto SPR1PTH = bsp.chipset[Chipset::Register::SPR1PTH];
constexpr auto SPR2PTH = bsp.chipset[Chipset::Register::SPR2PTH];
constexpr auto SPR3PTH = bsp.chipset[Chipset::Register::SPR3PTH];
constexpr auto SPR4PTH = bsp.chipset[Chipset::Register::SPR4PTH];
constexpr auto SPR5PTH = bsp.chipset[Chipset::Register::SPR5PTH];
constexpr auto SPR6PTH = bsp.chipset[Chipset::Register::SPR6PTH];
constexpr auto SPR7PTH = bsp.chipset[Chipset::Register::SPR7PTH];
constexpr auto INTENAR = bsp.chipset[Chipset::Register::INTENAR];
constexpr auto INTREQR = bsp.chipset[Chipset::Register::INTREQR];
constexpr auto INTREQ  = bsp.chipset[Chipset::Register::INTREQ];
constexpr auto INTENA  = bsp.chipset[Chipset::Register::INTENA];
constexpr auto BPLCON0 = bsp.chipset[Chipset::Register::BPLCON0];
constexpr auto BPLCON1 = bsp.chipset[Chipset::Register::BPLCON1];
constexpr auto BPLCON2 = bsp.chipset[Chipset::Register::BPLCON2]; 
constexpr auto BPL1MOD = bsp.chipset[Chipset::Register::BPL1MOD];
constexpr auto DDFSTRT = bsp.chipset[Chipset::Register::DDFSTRT];
constexpr auto DDFSTOP = bsp.chipset[Chipset::Register::DDFSTOP];  
constexpr auto DIWSTRT = bsp.chipset[Chipset::Register::DIWSTRT];
constexpr auto DIWSTOP = bsp.chipset[Chipset::Register::DIWSTOP];
constexpr auto COLOR00 = bsp.chipset[Chipset::Register::COLOR00];
constexpr auto COLOR01 = bsp.chipset[Chipset::Register::COLOR01];
constexpr auto COLOR17 = bsp.chipset[Chipset::Register::COLOR17];
constexpr auto COLOR18 = bsp.chipset[Chipset::Register::COLOR18];
constexpr auto COLOR19 = bsp.chipset[Chipset::Register::COLOR19];
constexpr auto COP1LCH = bsp.chipset[Chipset::Register::COP1LCH];
constexpr auto COPJMP1 = bsp.chipset[Chipset::Register::COPJMP1];
constexpr auto DMACON  = bsp.chipset[Chipset::Register::DMACON];

struct spaceship_sprite_t {
  spaceship_sprite_t() {
    data[0] = 0x6D60;
    data[1] = 0x7200;
    data[2] = 0x0990;
    data[3] = 0x07E0;
    data[4] = 0x13C8;
    data[5] = 0x0FF0;
    data[6] = 0x23C4;
    data[7] = 0x1FF8;
    data[8] = 0x13C8;
    data[9] = 0x0FF0;
    data[10] = 0x0990;
    data[11] = 0x07E0;
    data[12] = 0;
    data[13] = 0;
  }
  volatile uint16_t data[14];
};

struct dummy_sprite_t {
  dummy_sprite_t() {
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
  }
  volatile uint32_t data[4];
};

struct bitplane_t {
  static constexpr auto bytes = 8000U;
  bitplane_t() {
    for(auto i = 0 ; i < bytes/4 ; ++i)
      data[i] = 0xFFFFFFFF;
  }
  volatile uint32_t data[bytes/4];
};

template<int N, int vstart, int vstop>
struct copperlist_t {
  copperlist_t(const bitplane_t& bpl,
	       const spaceship_sprite_t& ss,
	       const star_sprite_t<N,vstart,vstop>& star,
	       const dummy_sprite_t& ds)
    : i_move_bitplane{&bpl}
    , i_move_sprite_0{&ss}
    , i_move_sprite_1{&star}
    , i_move_sprite_2{&ds}
    , i_move_sprite_3{&ds}
    , i_move_sprite_4{&ds}
    , i_move_sprite_5{&ds}
    , i_move_sprite_6{&ds}
    , i_move_sprite_7{&ds}
  { }
  
  volatile copper::move_l<BPL1PTH> i_move_bitplane;
  volatile copper::move_l<SPR0PTH> i_move_sprite_0;
  volatile copper::move_l<SPR1PTH> i_move_sprite_1;
  volatile copper::move_l<SPR2PTH> i_move_sprite_2;
  volatile copper::move_l<SPR3PTH> i_move_sprite_3;
  volatile copper::move_l<SPR4PTH> i_move_sprite_4;
  volatile copper::move_l<SPR5PTH> i_move_sprite_5;
  volatile copper::move_l<SPR6PTH> i_move_sprite_6;
  volatile copper::move_l<SPR7PTH> i_move_sprite_7;
  volatile copper::exit            i_exit;
};

extern "C" void interrupt_handler() {
}

__attribute__((section(".startup_code"))) int main() {

  // INSTALL INTERRUPT HANDLERS
  asm("movel #interrupt_handler,%a0\n\t"
      :
      : "r" (interrupt_handler));
  
  // STORE AWAY AND TURN OFF INTERRUPTS
  
  const auto int_vector = read_w<INTENAR>();
  write_w<INTENA>(0x7FDF);
  write_w<INTENA>(0x8020);

  // CONFIGURE DATA
  
  // NOTE: This only works if there is only Chip RAM, the reason for
  // this is that the sprite data have to be in chip ram but if there
  // is slow ram the stack will be placed there. Not sure how to solve
  // this yet but for this demo it is ok.
  spaceship_sprite_t          spaceship_sprite{};
  dummy_sprite_t              dummy_sprite{};
  star_sprite_t<40,0x2C,0xF4> star_sprite{};
  bitplane_t                  bitplane{};
  copperlist_t                copperlist{bitplane, spaceship_sprite, star_sprite, dummy_sprite};
  
  // SET UP FOR A SINGLE BITPLANE
  
  write_w<BPLCON0>(0x1200); // 1 bit-plane, color is on
  write_w<BPL1MOD>(0x0000); // Modulo = 0
  write_w<BPLCON1>(0x0000); // Horizontal scroll value = 0
  write_w<BPLCON2>(0x0024); // Sprites have priority over playfields
  write_w<DDFSTRT>(0x0038); // Set data-fetch start
  write_w<DDFSTOP>(0x00D0); // Set data-fetch stop
  write_w<DIWSTRT>(0x2C81); // Set display window start
  write_w<DIWSTOP>(0xF4C1); // Set display window stop
  
  // SET UP COLOR REGISTERS
  
  write_w<COLOR00>(0x0000);
  write_w<COLOR01>(0x0000);
  write_w<COLOR17>(0x0444);
  write_w<COLOR18>(0x0999);
  write_w<COLOR19>(0x0FFF);  

  // POINT COPPER AT COPPER LIST AND START DMA
  write_l<COP1LCH>(&copperlist); // Point copper at copper list
  read_w<COPJMP1>();             // Force start copper
  write_w<DMACON>(0x83A0);       // Enable dma

  while(!mouse_clicked(bsp))
    if(read_w<INTREQR>() & 0x0020) {
      write_w<INTREQ>(0x0020);
      star_sprite.tick();
    }

  // RESTORE INTERRUPTS
  
  write_w<INTENA>(int_vector | 0x8000);
  return 0;
}
	   
