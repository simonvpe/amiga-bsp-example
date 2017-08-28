#pragma once
#include "cmap.hpp"
#include "common/utils.hpp"

// See http://amiga-dev.wikidot.com/information:hardware

namespace Chipset {
  using cmap::map;
  using cmap::make_lookup;

  enum class Register {
    BSTDAT, DMACONR, VPOSR, VHPOSR,
    DSKDATR, JOY0DAT, JOY1DAT, CLXDAT, ADKCONR, POT0DAT, POT1DAT, POTINP, SERDATR, DSKBYTR,
    INTENAR, INTREQR, DSKPTH, DSKPTL, DSKLEN, DSKDAT, REFPTR, VPOSW, VHPOSW, COPCON, SERDAT,
    SERPER, POTGO, JOYTEST, STREQU, STRVBL, STRHOR, STRLONG, BLTCON0, BLTCON1, BLTAFWM,
    BLTALWM, BLTCPTH, BLTCPTL, BLTBPTH, BLTBPTL, BLTAPTH, BLTAPTL, BLTDPTH, BLTDPTL, BLTSIZE,
    BLTCMOD, BLTBMOD, BLTAMOD, BLTDMOD, BLTCDAT, BLTBDAT, BLTADAT, DSKSYNC, COP1LCH, COP1LCL,
    COP2LCH, COP2LCL, COPJMP1, COPJMP2, COPINS, DIWSTRT, DIWSTOP, DDFSTRT, DDFSTOP, DMACON,
    CLXCON, INTENA, INTREQ, ADKCON, AUD0LCH, AUD0LCL, AUD0LEN, AUD0PER, AUD0VOL, AUD0DAT,
    AUD1LCH, AUD1LCL, AUD1LEN, AUD1PER, AUD1VOL, AUD1DAT, AUD2LCH, AUD2LCL, AUD2LEN, AUD2PER,
    AUD2VOL, AUD2DAT, AUD3LCH, AUD3LCL, AUD3LEN, AUD3PER, AUD3VOL, AUD3DAT, BPL1PTH, BPL1PTL,
    BPL2PTH, BPL2PTL, BPL3PTH, BPL3PTL, BPL4PTH, BPL4PTL, BPL5PTH, BPL5PTL, BPL6PTH, BPL6PTL,
    BPLCON0, BPLCON1, BPLCON2, BPLCON3, BPL1MOD, BPL2MOD, BPL1DAT, BPL2DAT, BPL3DAT, BPL4DAT,
    BPL5DAT, BPL6DAT, SPR0PTH, SPR0PTL, SPR1PTH, SPR1PTL, SPR2PTH, SPR2PTL, SPR3PTH, SPR3PTL,
    SPR4PTH, SPR4PTL, SPR5PTH, SPR5PTL, SPR6PTH, SPR6PTL, SPR7PTH, SPR7PTL, SPR0POS, SPR0CTL,
    SPR0DATA, SPR0DATB, SPR1POS, SPR1CTL, SPR1DATA, SPR1DATB, SPR2POS, SPR2CTL, SPR2DATA,
    SPR2DATB, SPR3POS, SPR3CTL, SPR3DATA, SPR3DATB, SPR4POS, SPR4CTL, SPR4DATA, SPR4DATB,
    SPR5POS, SPR5CTL, SPR5DATA, SPR5DATB, SPR6POS, SPR6CTL, SPR6DATA, SPR6DATB, SPR7POS,
    SPR7CTL, SPR7DATA, SPR7DATB, COLOR00, COLOR01, COLOR02, COLOR03, COLOR04, COLOR05,
    COLOR06, COLOR07, COLOR08, COLOR09, COLOR10, COLOR11, COLOR12, COLOR13, COLOR14, COLOR15,
    COLOR16, COLOR17, COLOR18, COLOR19, COLOR20, COLOR21, COLOR22, COLOR23, COLOR24, COLOR25,
    COLOR26, COLOR27, COLOR28, COLOR29, COLOR30, COLOR31, BEAMCON0,
  };

  constexpr auto ocs = make_lookup(
    map(Register::BSTDAT,  reg{0xDFF000, Width::W, Access::R}), // Blitter dest. early read (dummy address)	
    map(Register::DMACONR, reg{0xDFF002, Width::W, Access::R}), // Dma control (and blitter status) read
    map(Register::VPOSR,   reg{0xDFF004, Width::W, Access::R}), // Read vertical most sig. bits (and frame flop)
    map(Register::VHPOSR,  reg{0xDFF006, Width::W, Access::R}), // Read vert and horiz position of beam				
    map(Register::DSKDATR, reg{0xDFF008, Width::W, Access::R}), // Disk data early read (dummy address)         
    map(Register::JOY0DAT, reg{0xDFF00A, Width::W, Access::R}), // Joystick-mouse 0 data (vert, horiz)          
    map(Register::JOY1DAT, reg{0xDFF00C, Width::W, Access::R}), // Joystick-mouse 1 data (vert, horiz)          
    map(Register::CLXDAT,  reg{0xDFF00E, Width::W, Access::R}), // Collision data reg. (read and clear)         
    map(Register::ADKCONR, reg{0xDFF010, Width::W, Access::R}), // Audio,disk control register read           
    map(Register::POT0DAT, reg{0xDFF012, Width::W, Access::R}), // Pot counter data left pair (vert, horiz)        
    map(Register::POT1DAT, reg{0xDFF014, Width::W, Access::R}), // Pot counter data right pair (vert, horiz)        
    map(Register::POTINP,  reg{0xDFF016, Width::W, Access::R}), // Pot pin data read           
    map(Register::SERDATR, reg{0xDFF018, Width::W, Access::R}), // Serial port data and status read         
    map(Register::DSKBYTR, reg{0xDFF01A, Width::W, Access::R}), // Disk data byte and status read         
    map(Register::INTENAR, reg{0xDFF01C, Width::W, Access::R}), // Interrupt enable bits read           
    map(Register::INTREQR, reg{0xDFF01E, Width::W, Access::R}), // Interrupt request bits read           
    map(Register::DSKPTH,  reg{0xDFF020, Width::W, Access::W}), // Disk pointer (high 5 bits, was 3 bits)       
    map(Register::DSKPTL,  reg{0xDFF022, Width::W, Access::W}), // Disk pointer (low 15 bits)          
    map(Register::DSKLEN,  reg{0xDFF024, Width::W, Access::W}), // Disk length             
    map(Register::DSKDAT,  reg{0xDFF026, Width::W, Access::W}), // Disk DMA data write           
    map(Register::REFPTR,  reg{0xDFF028, Width::W, Access::W}), // Refresh pointer             
    map(Register::VPOSW,   reg{0xDFF02A, Width::W, Access::W}), // Write vert most sig. bits (and frame flop)       
    map(Register::VHPOSW,  reg{0xDFF02C, Width::W, Access::W}), // Write vert and horiz pos of beam        
    map(Register::COPCON,  reg{0xDFF02E, Width::W, Access::W}), // Coprocessor control             
    map(Register::SERDAT,  reg{0xDFF030, Width::W, Access::W}), // Serial port data and stop bits write        
    map(Register::SERPER,  reg{0xDFF032, Width::W, Access::W}), // Serial port period and control          
    map(Register::POTGO,   reg{0xDFF034, Width::W, Access::W}), // Pot count start,pot pin drive enable data        
    map(Register::JOYTEST, reg{0xDFF036, Width::W, Access::W}), // Write to all 4 joystick-mouse counters at once       
    map(Register::STREQU,  reg{0xDFF038, Width::W, Access::S}), // Strobe for horiz sync with VB and EQU       
    map(Register::STRVBL,  reg{0xDFF03A, Width::W, Access::S}), // Strobe for horiz sync with VB (vert blank)       
    map(Register::STRHOR,  reg{0xDFF03C, Width::W, Access::S}), // Strobe for horiz sync           
    map(Register::STRLONG, reg{0xDFF03E, Width::W, Access::S}), // Strobe for identification of long horiz line        
    map(Register::BLTCON0, reg{0xDFF040, Width::W, Access::W}), // Blitter control register 0           
    map(Register::BLTCON1, reg{0xDFF042, Width::W, Access::W}), // Blitter control register 1           
    map(Register::BLTAFWM, reg{0xDFF044, Width::W, Access::W}), // Blitter first word mask for source A        
    map(Register::BLTALWM, reg{0xDFF046, Width::W, Access::W}), // Blitter last word mask for source A        
    map(Register::BLTCPTH, reg{0xDFF048, Width::W, Access::W}), // Blitter pointer to source C (high 5 bits, was 3 bits)    
    map(Register::BLTCPTL, reg{0xDFF04A, Width::W, Access::W}), // Blitter pointer to source C (low 15 bits)       
    map(Register::BLTBPTH, reg{0xDFF04C, Width::W, Access::W}), // Blitter pointer to source B (high 5 bits, was 3 bits)    
    map(Register::BLTBPTL, reg{0xDFF04E, Width::W, Access::W}), // Blitter pointer to source B (low 15 bits)       
    map(Register::BLTAPTH, reg{0xDFF050, Width::W, Access::W}), // Blitter pointer to source A (high 5 bits, was 3 bits)    
    map(Register::BLTAPTL, reg{0xDFF052, Width::W, Access::W}), // Blitter pointer to source A (low 15 bits)       
    map(Register::BLTDPTH, reg{0xDFF054, Width::W, Access::W}), // Blitter pointer to dest D (high 5 bits, was 3 bits)    
    map(Register::BLTDPTL, reg{0xDFF056, Width::W, Access::W}), // Blitter pointer to dest D (low 15 bits)       
    map(Register::BLTSIZE, reg{0xDFF058, Width::W, Access::W}), // Blitter start and size (win/width,height)          
    map(Register::BLTCMOD, reg{0xDFF060, Width::W, Access::W}), // Blitter modulo for source C          
    map(Register::BLTBMOD, reg{0xDFF062, Width::W, Access::W}), // Blitter modulo for source B          
    map(Register::BLTAMOD, reg{0xDFF064, Width::W, Access::W}), // Blitter modulo for source A          
    map(Register::BLTDMOD, reg{0xDFF066, Width::W, Access::W}), // Blitter modulo for dest D          
    map(Register::BLTCDAT, reg{0xDFF070, Width::W, Access::W}), // Blitter source C data register          
    map(Register::BLTBDAT, reg{0xDFF072, Width::W, Access::W}), // Blitter source B data register          
    map(Register::BLTADAT, reg{0xDFF074, Width::W, Access::W}), // Blitter source A data register          
    map(Register::DSKSYNC, reg{0xDFF07E, Width::W, Access::W}), // Disk sync pattern reg for disk read        
    map(Register::COP1LCH, reg{0xDFF080, Width::W, Access::W}), // Coprocessor 1st location (high 5 bits,was 3 bits)       
    map(Register::COP1LCL, reg{0xDFF082, Width::W, Access::W}), // Coprocessor 1st location (low 15 bits)         
    map(Register::COP2LCH, reg{0xDFF084, Width::W, Access::W}), // Coprocessor 2nd location(high 5 bits,was 3 bits)        
    map(Register::COP2LCL, reg{0xDFF086, Width::W, Access::W}), // Coprocessor 2nd location (low 15 bits)         
    map(Register::COPJMP1, reg{0xDFF088, Width::W, Access::S}), // Coprocessor restart at 1st location          
    map(Register::COPJMP2, reg{0xDFF08A, Width::W, Access::S}), // Coprocessor restart at 2nd location          
    map(Register::COPINS,  reg{0xDFF08C, Width::W, Access::S}), // Coprocessor inst fetch identify           
    map(Register::DIWSTRT, reg{0xDFF08E, Width::W, Access::W}), // Display window start (upper left vert,horiz pos)        
    map(Register::DIWSTOP, reg{0xDFF090, Width::W, Access::W}), // Display window stop (lower right vert,horiz pos)        
    map(Register::DDFSTRT, reg{0xDFF092, Width::W, Access::W}), // Display bit plane data fetch start,horiz pos        
    map(Register::DDFSTOP, reg{0xDFF094, Width::W, Access::W}), // Display bit plane data fetch stop,horiz pos        
    map(Register::DMACON,  reg{0xDFF096, Width::W, Access::W}), // DMA control write (clear or set)         
    map(Register::CLXCON,  reg{0xDFF098, Width::W, Access::W}), // Collision control             
    map(Register::INTENA,  reg{0xDFF09A, Width::W, Access::W}), // Interrupt enable bits (clear or set bits)        
    map(Register::INTREQ,  reg{0xDFF09C, Width::W, Access::W}), // Interrupt request bits (clear or set bits)        
    map(Register::ADKCON,  reg{0xDFF09E, Width::W, Access::W}), // Audio,disk,UART control             
    map(Register::AUD0LCH, reg{0xDFF0A0, Width::W, Access::W}), // Audio channel 0 location (high 5 bits was 3 bits)     
    map(Register::AUD0LCL, reg{0xDFF0A2, Width::W, Access::W}), // Audio channel 0 location (low 15 bits)        
    map(Register::AUD0LEN, reg{0xDFF0A4, Width::W, Access::W}), // Audio channel 0 length           
    map(Register::AUD0PER, reg{0xDFF0A6, Width::W, Access::W}), // Audio channel 0 period           
    map(Register::AUD0VOL, reg{0xDFF0A8, Width::W, Access::W}), // Audio channel 0 volume           
    map(Register::AUD0DAT, reg{0xDFF0AA, Width::W, Access::W}), // Audio channel 0 data           
    map(Register::AUD1LCH, reg{0xDFF0B0, Width::W, Access::W}), // Audio channel 1 location (high 5 bits was 3 bits)     
    map(Register::AUD1LCL, reg{0xDFF0B2, Width::W, Access::W}), // Audio channel 1 location (low 15 bits)        
    map(Register::AUD1LEN, reg{0xDFF0B4, Width::W, Access::W}), // Audio channel 1 length           
    map(Register::AUD1PER, reg{0xDFF0B6, Width::W, Access::W}), // Audio channel 1 period           
    map(Register::AUD1VOL, reg{0xDFF0B8, Width::W, Access::W}), // Audio channel 1 volume           
    map(Register::AUD1DAT, reg{0xDFF0BA, Width::W, Access::W}), // Audio channel 1 data           
    map(Register::AUD2LCH, reg{0xDFF0C0, Width::W, Access::W}), // Audio channel 2 location (high 5 bits was 3 bits)     
    map(Register::AUD2LCL, reg{0xDFF0C2, Width::W, Access::W}), // Audio channel 2 location (low 15 bits)        
    map(Register::AUD2LEN, reg{0xDFF0C4, Width::W, Access::W}), // Audio channel 2 length           
    map(Register::AUD2PER, reg{0xDFF0C6, Width::W, Access::W}), // Audio channel 2 period           
    map(Register::AUD2VOL, reg{0xDFF0C8, Width::W, Access::W}), // Audio channel 2 volume           
    map(Register::AUD2DAT, reg{0xDFF0CA, Width::W, Access::W}), // Audio channel 2 data           
    map(Register::AUD3LCH, reg{0xDFF0D0, Width::W, Access::W}), // Audio channel 3 location (high 5 bits was 3 bits)     
    map(Register::AUD3LCL, reg{0xDFF0D2, Width::W, Access::W}), // Audio channel 3 location (low 15 bits)        
    map(Register::AUD3LEN, reg{0xDFF0D4, Width::W, Access::W}), // Audio channel 3 length           
    map(Register::AUD3PER, reg{0xDFF0D6, Width::W, Access::W}), // Audio channel 3 period           
    map(Register::AUD3VOL, reg{0xDFF0D8, Width::W, Access::W}), // Audio channel 3 volume           
    map(Register::AUD3DAT, reg{0xDFF0DA, Width::W, Access::W}), // Audio channel 3 data           
    map(Register::BPL1PTH, reg{0xDFF0E0, Width::W, Access::W}), // Bitplane pointer 1 (high 5 bits was 3 bits)      
    map(Register::BPL1PTL, reg{0xDFF0E2, Width::W, Access::W}), // Bitplane pointer 1 (low 15 bits)         
    map(Register::BPL2PTH, reg{0xDFF0E4, Width::W, Access::W}), // Bitplane pointer 2 (high 5 bits was 3 bits)      
    map(Register::BPL2PTL, reg{0xDFF0E6, Width::W, Access::W}), // Bitplane pointer 2 (low 15 bits)         
    map(Register::BPL3PTH, reg{0xDFF0E8, Width::W, Access::W}), // Bitplane pointer 3 (high 5 bits was 3 bits)      
    map(Register::BPL3PTL, reg{0xDFF0EA, Width::W, Access::W}), // Bitplane pointer 3 (low 15 bits)         
    map(Register::BPL4PTH, reg{0xDFF0EC, Width::W, Access::W}), // Bitplane pointer 4 (high 5 bits was 3 bits)      
    map(Register::BPL4PTL, reg{0xDFF0EE, Width::W, Access::W}), // Bitplane pointer 4 (low 15 bits)         
    map(Register::BPL5PTH, reg{0xDFF0F0, Width::W, Access::W}), // Bitplane pointer 5 (high 5 bits was 3 bits)      
    map(Register::BPL5PTL, reg{0xDFF0F2, Width::W, Access::W}), // Bitplane pointer 5 (low 15 bits)         
    map(Register::BPL6PTH, reg{0xDFF0F4, Width::W, Access::W}), // Bitplane pointer 6 (high 5 bits was 3 bits)      
    map(Register::BPL6PTL, reg{0xDFF0F6, Width::W, Access::W}), // Bitplane pointer 6 (low 15 bits)         
    map(Register::BPLCON0, reg{0xDFF100, Width::W, Access::W}), // Bitplane control (miscellaneous control bits)          
    map(Register::BPLCON1, reg{0xDFF102, Width::W, Access::W}), // Bitplane control (scroll value)           
    map(Register::BPLCON2, reg{0xDFF104, Width::W, Access::W}), // Bitplane control (video priority control)          
    map(Register::BPLCON3, reg{0xDFF106, Width::W, Access::W}), // Bitplane control (enhanced features)           
    map(Register::BPL1MOD, reg{0xDFF108, Width::W, Access::W}), // Bitplane modulo (odd planes)           
    map(Register::BPL2MOD, reg{0xDFF10A, Width::W, Access::W}), // Bitplane modulo (even planes)           
    map(Register::BPL1DAT, reg{0xDFF110, Width::W, Access::W}), // Bitplane 1 data (parallel to serial convert)        
    map(Register::BPL2DAT, reg{0xDFF112, Width::W, Access::W}), // Bitplane 2 data (parallel to serial convert)        
    map(Register::BPL3DAT, reg{0xDFF114, Width::W, Access::W}), // Bitplane 3 data (parallel to serial convert)        
    map(Register::BPL4DAT, reg{0xDFF116, Width::W, Access::W}), // Bitplane 4 data (parallel to serial convert)        
    map(Register::BPL5DAT, reg{0xDFF118, Width::W, Access::W}), // Bitplane 5 data (parallel to serial convert)        
    map(Register::BPL6DAT, reg{0xDFF11A, Width::W, Access::W}), // Bitplane 6 data (parallel to serial convert)        
    map(Register::SPR0PTH, reg{0xDFF120, Width::W, Access::W}), // Sprite 0 pointer (high 5 bits was 3 bits)      
    map(Register::SPR0PTL, reg{0xDFF122, Width::W, Access::W}), // Sprite 0 pointer (low 15 bits)         
    map(Register::SPR1PTH, reg{0xDFF124, Width::W, Access::W}), // Sprite 1 pointer (high 5 bits was 3 bits)      
    map(Register::SPR1PTL, reg{0xDFF126, Width::W, Access::W}), // Sprite 1 pointer (low 15 bits)         
    map(Register::SPR2PTH, reg{0xDFF128, Width::W, Access::W}), // Sprite 2 pointer (high 5 bits was 3 bits)      
    map(Register::SPR2PTL, reg{0xDFF12A, Width::W, Access::W}), // Sprite 2 pointer (low 15 bits)         
    map(Register::SPR3PTH, reg{0xDFF12C, Width::W, Access::W}), // Sprite 3 pointer (high 5 bits was 3 bits)      
    map(Register::SPR3PTL, reg{0xDFF12E, Width::W, Access::W}), // Sprite 3 pointer (low 15 bits)         
    map(Register::SPR4PTH, reg{0xDFF130, Width::W, Access::W}), // Sprite 4 pointer (high 5 bits was 3 bits)      
    map(Register::SPR4PTL, reg{0xDFF132, Width::W, Access::W}), // Sprite 4 pointer (low 15 bits)         
    map(Register::SPR5PTH, reg{0xDFF134, Width::W, Access::W}), // Sprite 5 pointer (high 5 bits was 3 bits)      
    map(Register::SPR5PTL, reg{0xDFF136, Width::W, Access::W}), // Sprite 5 pointer (low 15 bits)         
    map(Register::SPR6PTH, reg{0xDFF138, Width::W, Access::W}), // Sprite 6 pointer (high 5 bits was 3 bits)      
    map(Register::SPR6PTL, reg{0xDFF13A, Width::W, Access::W}), // Sprite 6 pointer (low 15 bits)         
    map(Register::SPR7PTH, reg{0xDFF13C, Width::W, Access::W}), // Sprite 7 pointer (high 5 bits was 3 bits)      
    map(Register::SPR7PTL, reg{0xDFF13E, Width::W, Access::W}), // Sprite 7 pointer (low 15 bits)         
    map(Register::SPR0POS, reg{0xDFF140, Width::W, Access::W}), // Sprite 0 vert,horiz start pos data         
    map(Register::SPR0CTL, reg{0xDFF142, Width::W, Access::W}), // Sprite 0 position and control data         
    map(Register::SPR0DATA,reg{0xDFF144, Width::W, Access::W}), // Sprite 0 image data register A         
    map(Register::SPR0DATB,reg{0xDFF146, Width::W, Access::W}), // Sprite 0 image data register B         
    map(Register::SPR1POS, reg{0xDFF148, Width::W, Access::W}), // Sprite 1 vert,horiz start pos data         
    map(Register::SPR1CTL, reg{0xDFF14A, Width::W, Access::W}), // Sprite 1 position and control data         
    map(Register::SPR1DATA,reg{0xDFF14C, Width::W, Access::W}), // Sprite 1 image data register A         
    map(Register::SPR1DATB,reg{0xDFF14E, Width::W, Access::W}), // Sprite 1 image data register B         
    map(Register::SPR2POS, reg{0xDFF150, Width::W, Access::W}), // Sprite 2 vert,horiz start pos data         
    map(Register::SPR2CTL, reg{0xDFF152, Width::W, Access::W}), // Sprite 2 position and control data         
    map(Register::SPR2DATA,reg{0xDFF154, Width::W, Access::W}), // Sprite 2 image data register A         
    map(Register::SPR2DATB,reg{0xDFF156, Width::W, Access::W}), // Sprite 2 image data register B         
    map(Register::SPR3POS, reg{0xDFF158, Width::W, Access::W}), // Sprite 3 vert,horiz start pos data         
    map(Register::SPR3CTL, reg{0xDFF15A, Width::W, Access::W}), // Sprite 3 position and control data         
    map(Register::SPR3DATA,reg{0xDFF15C, Width::W, Access::W}), // Sprite 3 image data register A         
    map(Register::SPR3DATB,reg{0xDFF15E, Width::W, Access::W}), // Sprite 3 image data register B         
    map(Register::SPR4POS, reg{0xDFF160, Width::W, Access::W}), // Sprite 4 vert,horiz start pos data         
    map(Register::SPR4CTL, reg{0xDFF162, Width::W, Access::W}), // Sprite 4 position and control data         
    map(Register::SPR4DATA,reg{0xDFF164, Width::W, Access::W}), // Sprite 4 image data register A         
    map(Register::SPR4DATB,reg{0xDFF166, Width::W, Access::W}), // Sprite 4 image data register B         
    map(Register::SPR5POS, reg{0xDFF168, Width::W, Access::W}), // Sprite 5 vert,horiz start pos data         
    map(Register::SPR5CTL, reg{0xDFF16A, Width::W, Access::W}), // Sprite 5 position and control data         
    map(Register::SPR5DATA,reg{0xDFF16C, Width::W, Access::W}), // Sprite 5 image data register A         
    map(Register::SPR5DATB,reg{0xDFF16E, Width::W, Access::W}), // Sprite 5 image data register B         
    map(Register::SPR6POS, reg{0xDFF170, Width::W, Access::W}), // Sprite 6 vert,horiz start pos data         
    map(Register::SPR6CTL, reg{0xDFF172, Width::W, Access::W}), // Sprite 6 position and control data         
    map(Register::SPR6DATA,reg{0xDFF174, Width::W, Access::W}), // Sprite 6 image data register A         
    map(Register::SPR6DATB,reg{0xDFF176, Width::W, Access::W}), // Sprite 6 image data register B         
    map(Register::SPR7POS, reg{0xDFF178, Width::W, Access::W}), // Sprite 7 vert,horiz start pos data         
    map(Register::SPR7CTL, reg{0xDFF17A, Width::W, Access::W}), // Sprite 7 position and control data         
    map(Register::SPR7DATA,reg{0xDFF17C, Width::W, Access::W}), // Sprite 7 image data register A         
    map(Register::SPR7DATB,reg{0xDFF17E, Width::W, Access::W}), // Sprite 7 image data register B         
    map(Register::COLOR00, reg{0xDFF180, Width::W, Access::W}), // Color table 0            
    map(Register::COLOR01, reg{0xDFF182, Width::W, Access::W}), // Color table 1            
    map(Register::COLOR02, reg{0xDFF184, Width::W, Access::W}), // Color table 2            
    map(Register::COLOR03, reg{0xDFF186, Width::W, Access::W}), // Color table 3            
    map(Register::COLOR04, reg{0xDFF188, Width::W, Access::W}), // Color table 4            
    map(Register::COLOR05, reg{0xDFF18A, Width::W, Access::W}), // Color table 5            
    map(Register::COLOR06, reg{0xDFF18C, Width::W, Access::W}), // Color table 6            
    map(Register::COLOR07, reg{0xDFF18E, Width::W, Access::W}), // Color table 7            
    map(Register::COLOR08, reg{0xDFF190, Width::W, Access::W}), // Color table 8            
    map(Register::COLOR09, reg{0xDFF192, Width::W, Access::W}), // Color table 9            
    map(Register::COLOR10, reg{0xDFF194, Width::W, Access::W}), // Color table 10            
    map(Register::COLOR11, reg{0xDFF196, Width::W, Access::W}), // Color table 11            
    map(Register::COLOR12, reg{0xDFF198, Width::W, Access::W}), // Color table 12            
    map(Register::COLOR13, reg{0xDFF19A, Width::W, Access::W}), // Color table 13            
    map(Register::COLOR14, reg{0xDFF19C, Width::W, Access::W}), // Color table 14            
    map(Register::COLOR15, reg{0xDFF19E, Width::W, Access::W}), // Color table 15            
    map(Register::COLOR16, reg{0xDFF1A0, Width::W, Access::W}), // Color table 16            
    map(Register::COLOR17, reg{0xDFF1A2, Width::W, Access::W}), // Color table 17            
    map(Register::COLOR18, reg{0xDFF1A4, Width::W, Access::W}), // Color table 18            
    map(Register::COLOR19, reg{0xDFF1A6, Width::W, Access::W}), // Color table 19            
    map(Register::COLOR20, reg{0xDFF1A8, Width::W, Access::W}), // Color table 20            
    map(Register::COLOR21, reg{0xDFF1AA, Width::W, Access::W}), // Color table 21            
    map(Register::COLOR22, reg{0xDFF1AC, Width::W, Access::W}), // Color table 22            
    map(Register::COLOR23, reg{0xDFF1AE, Width::W, Access::W}), // Color table 23            
    map(Register::COLOR24, reg{0xDFF1B0, Width::W, Access::W}), // Color table 24            
    map(Register::COLOR25, reg{0xDFF1B2, Width::W, Access::W}), // Color table 25            
    map(Register::COLOR26, reg{0xDFF1B4, Width::W, Access::W}), // Color table 26            
    map(Register::COLOR27, reg{0xDFF1B6, Width::W, Access::W}), // Color table 27            
    map(Register::COLOR28, reg{0xDFF1B8, Width::W, Access::W}), // Color table 28            
    map(Register::COLOR29, reg{0xDFF1BA, Width::W, Access::W}), // Color table 29            
    map(Register::COLOR30, reg{0xDFF1BC, Width::W, Access::W}), // Color table 30            
    map(Register::COLOR31, reg{0xDFF1BE, Width::W, Access::W}), // Color table 31            
    map(Register::BEAMCON0,reg{0xDFF1DC, Width::W, Access::W})  // Beam counter control register (SHRES,UHRES,PAL)          
  );
};
