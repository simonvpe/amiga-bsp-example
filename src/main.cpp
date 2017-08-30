#include "a500.hpp"
#include "drivers/mouse.hpp"

#include <array>

struct spaceship_sprite_t {
  spaceship_sprite_t() {
    data[0] = 0x6D40;
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

static volatile uint16_t copperlist[38];

void init_copperlist(
    const volatile void* sprite,
    const volatile void* dummy_sprite,
    const volatile void* bitplane) {

  const auto hi = [](const auto* ptr) -> uint16_t
  { return reinterpret_cast<uint32_t>(ptr) >> 16; };
  
  const auto lo = [](const auto* ptr) -> uint16_t
  { return reinterpret_cast<uint32_t>(ptr) & 0xFFFF; };

  copperlist[0] = 0x00E0;
  copperlist[1] = hi(bitplane);
  copperlist[2] = 0x00E2;
  copperlist[3] = lo(bitplane);
  copperlist[4] = 0x0120;
  copperlist[5] = hi(sprite);
  copperlist[6] = 0x0122;
  copperlist[7] = lo(sprite);
  copperlist[8] = 0x0124;
  copperlist[9] = hi(dummy_sprite);
  copperlist[10] = 0x0126;
  copperlist[11] = lo(dummy_sprite);
  copperlist[12] = 0x0128;
  copperlist[13] = hi(dummy_sprite);
  copperlist[14] = 0x012A;
  copperlist[15] = lo(dummy_sprite);
  copperlist[16] = 0x012C;
  copperlist[17] = hi(dummy_sprite);
  copperlist[18] = 0x012E;
  copperlist[19] = lo(dummy_sprite);
  copperlist[20] = 0x0130;
  copperlist[21] = hi(dummy_sprite);
  copperlist[22] = 0x0132;
  copperlist[23] = lo(dummy_sprite);
  copperlist[24] = 0x0134;
  copperlist[25] = hi(dummy_sprite);
  copperlist[26] = 0x0136;
  copperlist[27] = lo(dummy_sprite);
  copperlist[28] = 0x0138;
  copperlist[29] = hi(dummy_sprite);
  copperlist[30] = 0x013A;
  copperlist[31] = lo(dummy_sprite);
  copperlist[32] = 0x013C;
  copperlist[33] = hi(dummy_sprite);
  copperlist[34] = 0x013E;
  copperlist[35] = lo(dummy_sprite);
  copperlist[36] = 0xFFFF;
  copperlist[37] = 0xFFFE;
}

__attribute__((section(".startup_code"))) int main() {
  
  // SHORTAND ALL THE REGISTERS NEEDED
  
  constexpr auto INTENAR = bsp.chipset[Chipset::Register::INTENAR];
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
  
  // STORE AWAY AND TURN OFF INTERRUPTS
  
  const auto int_vector = read_w<INTENAR>();
  write_w<INTENA>(0x7fff);

  // CONFIGURE DATA
  
  // NOTE: This only works if there is only Chip RAM, the reason for
  // this is that the sprite data have to be in chip ram but if there
  // is slow ram the stack will be placed there. Not sure how to solve
  // this yet but for this demo it is ok.
  spaceship_sprite_t spaceship_sprite{};
  dummy_sprite_t     dummy_sprite{};
  bitplane_t         bitplane{};
  
  init_copperlist(&spaceship_sprite, &dummy_sprite, &bitplane);
  
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
  
  write_w<COLOR00>(0x0808);
  write_w<COLOR01>(0x0060);
  write_w<COLOR17>(0x0FF0);
  write_w<COLOR18>(0x00FF);
  write_w<COLOR19>(0x0F0F);  

  // POINT COPPER AT COPPER LIST AND START DMA
  write_l<COP1LCH>(&copperlist); // Point copper at copper list
  read_w<COPJMP1>();             // Force start copper
  write_w<DMACON>(0x83A0);       // Enable dma

  while(!mouse_clicked(bsp))
    ;
  
  write_w<INTENA>(int_vector | 0x8000);
  return 0;
}
	   
