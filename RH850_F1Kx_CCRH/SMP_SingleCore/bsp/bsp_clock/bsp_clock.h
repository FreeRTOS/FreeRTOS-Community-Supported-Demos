/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018 - 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

#ifndef BSP_CLOCK_H
#define BSP_CLOCK_H

/***********************************************************************************************************************
* Macro definitions (Register bit)
***********************************************************************************************************************/

/*
 *  MainOSC Enable Register (MOSCE)
 */

/* MainOSC disable trigger (MOSCDISTRG) */
#define _CGC_MAINOSC_STOP     ( 0x00000002UL )                  /* Stops MainOSC */
/* MainOSC enable trigger (MOSCENTRG) */
#define _CGC_MAINOSC_START    ( 0x00000001UL )                  /* Starts MainOSC */

/*
 *  MainOSC Status Register (MOSCS)
 */

/* MainOSC active status (MOSCCLKACT) */
#define _CGC_MAINOSC_ACTIVE    ( 0x00000004UL )                 /* MainOSC is active */

/*
 *  MainOSC Control Register (MOSCC)
 */

/* MainOSC amplification gain selection */
#define _CGC_MAINOSC_24MHZ    ( 0x00000000UL )                  /* 24MHz */
#define _CGC_MAINOSC_20MHZ    ( 0x00000001UL )                  /* 20MHz */
#define _CGC_MAINOSC_16MHZ    ( 0x00000002UL )                  /* 16MHz */
#define _CGC_MAINOSC_8MHZ     ( 0x00000003UL )                  /* 8MHz */

/*
 *  MainOSC Stop Mask Register (MOSCSTPM)
 */

/* MainOSC stop request mask (MOSCSTPMSK) */
#define _CGC_MAINOSC_REQUEST_STOP        ( 0x00000000UL )       /* MainOSC stops operation in standby mode */
#define _CGC_MAINOSC_REQUEST_CONTINUE    ( 0x00000001UL )       /* MainOSC continues operation in standby mode */

/*
 *  MainOSC Mode Control Register (MOSCM)
 */

/* MainOSC mode control (MOSCM) */
#define _CGC_MAINOSC_OSC_MODE      ( 0x00000000UL )             /* OSC mode */
#define _CGC_MAINOSC_EXCLK_MODE    ( 0x00000001UL )             /* EXCLK mode */

/*
 *  SubOSC Enable Register (SOSCE)
 */

/* SubOSC disable trigger (SOSCDISTRG) */
#define _CGC_SUBOSC_STOP     ( 0x00000002UL )                   /* Stops SubOSC */
/* SubOSC enable trigger (SOSCENTRG) */
#define _CGC_SUBOSC_START    ( 0x00000001UL )                   /* Starts SubOSC */

/*
 *  SubOSC Status Register (SOSCS)
 */

/* SubOSC activation status (SOSCCLKACT) */
#define _CGC_SUBOSC_ACTIVE    ( 0x00000004UL )                  /* SubOSC is active */

/*
 *  HS IntOSC Enable Register (ROSCE)
 */

/* HS IntOSC disable trigger (ROSCDISTRG) */
#define _CGC_HSOSC_STOP    ( 0x00000002UL )                     /* Stops HS IntOSC */

/*
 *  HS IntOSC Status Register (ROSCS)
 */

/* HS IntOSC active status (ROSCCLKACT) */
#define _CGC_HSOSC_INACTIVE    ( 0x00000000UL )                 /* HS IntOSC is inactive */
#define _CGC_HSOSC_ACTIVE      ( 0x00000004UL )                 /* HS IntOSC is active */

/*
 *  HS IntOSC Stop Mask Register (ROSCSTPM)
 */

/* HS IntOSC stop request mask (ROSCSTPMSK) */
#define _CGC_HSOSC_REQUEST_STOP        ( 0x00000000UL )         /* HS IntOSC stops operation in standby mode */
#define _CGC_HSOSC_REQUEST_CONTINUE    ( 0x00000001UL )         /* HS IntOSC continues operation in standby mode */

/*
 *  PLL0 Enable Register (PLL0E)
 */

/* PLL0 disable trigger (PLL0DISTRG) */
#define _CGC_PLL0_STOP     ( 0x00000002UL )                     /* Stops PLL0 */
/* PLL0 enable trigger (PLL0ENTRG) */
#define _CGC_PLL0_START    ( 0x00000001UL )                     /* Starts PLL0 */

/*
 *  PLL0 Status Register (PLL0S)
 */

/* PLL0 active status (PLL0CLKACT) */
#define _CGC_PLL0_ACTIVE    ( 0x00000004UL )                    /* PLL0 is active */

/*
 *  PLL0 Control Register (PLL0C)
 */

/* VCO output frequency range setting (PLL0FVV) */
#define _CGC_PLL0_VCO                    ( 0x60000000UL )       /* 440 MHz to 480 MHz. */
/* Frequency modulation cycle setting (PLL0MF) */
#define _CGC_PLL0_MFD10                  ( 0x00000000UL )       /* Modulation frequency division ratio MFD=10 */
#define _CGC_PLL0_MFD12                  ( 0x01000000UL )       /* Modulation frequency division ratio MFD=12 */
#define _CGC_PLL0_MFD18                  ( 0x02000000UL )       /* Modulation frequency division ratio MFD=18 */
#define _CGC_PLL0_MFD20                  ( 0x03000000UL )       /* Modulation frequency division ratio MFD=20 */
#define _CGC_PLL0_MFD22                  ( 0x04000000UL )       /* Modulation frequency division ratio MFD=22 */
#define _CGC_PLL0_MFD26                  ( 0x05000000UL )       /* Modulation frequency division ratio MFD=26 */
#define _CGC_PLL0_MFD28                  ( 0x06000000UL )       /* Modulation frequency division ratio MFD=28 */
#define _CGC_PLL0_MFD30                  ( 0x07000000UL )       /* Modulation frequency division ratio MFD=30 */
#define _CGC_PLL0_MFD34                  ( 0x08000000UL )       /* Modulation frequency division ratio MFD=34 */
#define _CGC_PLL0_MFD38                  ( 0x09000000UL )       /* Modulation frequency division ratio MFD=38 */
#define _CGC_PLL0_MFD40                  ( 0x0a000000UL )       /* Modulation frequency division ratio MFD=40 */
#define _CGC_PLL0_MFD44                  ( 0x0b000000UL )       /* Modulation frequency division ratio MFD=44 */
#define _CGC_PLL0_MFD50                  ( 0x0c000000UL )       /* Modulation frequency division ratio MFD=50 */
#define _CGC_PLL0_MFD56                  ( 0x0d000000UL )       /* Modulation frequency division ratio MFD=56 */
#define _CGC_PLL0_MFD58                  ( 0x0e000000UL )       /* Modulation frequency division ratio MFD=58 */
#define _CGC_PLL0_MFD60                  ( 0x0f000000UL )       /* Modulation frequency division ratio MFD=60 */
#define _CGC_PLL0_MFD62                  ( 0x10000000UL )       /* Modulation frequency division ratio MFD=62 */
#define _CGC_PLL0_MFD66                  ( 0x11000000UL )       /* Modulation frequency division ratio MFD=66 */
#define _CGC_PLL0_MFD72                  ( 0x12000000UL )       /* Modulation frequency division ratio MFD=72 */
#define _CGC_PLL0_MFD76                  ( 0x13000000UL )       /* Modulation frequency division ratio MFD=76 */
#define _CGC_PLL0_MFD80                  ( 0x14000000UL )       /* Modulation frequency division ratio MFD=80 */
#define _CGC_PLL0_MFD84                  ( 0x15000000UL )       /* Modulation frequency division ratio MFD=84 */
#define _CGC_PLL0_MFD86                  ( 0x16000000UL )       /* Modulation frequency division ratio MFD=86 */
#define _CGC_PLL0_MFD100                 ( 0x17000000UL )       /* Modulation frequency division ratio MFD=100 */
#define _CGC_PLL0_MFD120                 ( 0x18000000UL )       /* Modulation frequency division ratio MFD=120 */
#define _CGC_PLL0_MFD126                 ( 0x19000000UL )       /* Modulation frequency division ratio MFD=126 */
#define _CGC_PLL0_MFD134                 ( 0x1a000000UL )       /* Modulation frequency division ratio MFD=134 */
#define _CGC_PLL0_MFD150                 ( 0x1b000000UL )       /* Modulation frequency division ratio MFD=150 */
#define _CGC_PLL0_MFD166                 ( 0x1c000000UL )       /* Modulation frequency division ratio MFD=166 */
#define _CGC_PLL0_MFD200                 ( 0x1d000000UL )       /* Modulation frequency division ratio MFD=200 */
#define _CGC_PLL0_MFD250                 ( 0x1e000000UL )       /* Modulation frequency division ratio MFD=250 */
#define _CGC_PLL0_MFD300                 ( 0x1f000000UL )       /* Modulation frequency division ratio MFD=300 */
/* Frequency modulation range setting (PLL0ADJ) */
#define _CGC_PLL0_FMR_1                  ( 0x00000000UL )       /* Frequency modulation range 1% */
#define _CGC_PLL0_FMR_2                  ( 0x00100000UL )       /* Frequency modulation range 2% */
#define _CGC_PLL0_FMR_3                  ( 0x00200000UL )       /* Frequency modulation range 3% */
#define _CGC_PLL0_FMR_4                  ( 0x00300000UL )       /* Frequency modulation range 4% */
#define _CGC_PLL0_FMR_5                  ( 0x00400000UL )       /* Frequency modulation range 5% */
#define _CGC_PLL0_FMR_6                  ( 0x00500000UL )       /* Frequency modulation range 6% */
#define _CGC_PLL0_FMR_8                  ( 0x00600000UL )       /* Frequency modulation range 8% */
#define _CGC_PLL0_FMR_10                 ( 0x00700000UL )       /* Frequency modulation range 10% */
/* Operating mode setting (PLL0MD) */
#define _CGC_PLL0_SSCCG_MODE             ( 0x00004000UL )       /* SSCG mode (modulation frequency) */
/* Modulation mode setting in SSCG mode (PLL0SMD) */
#define _CGC_PLL0_SSCCG_MODU_MODE_SEL    ( 0x00002000UL )       /* Down spread modulation */

/*
 *  PLL0 Input Clock Selection Register (CKSC_PLL0IS_CTL)
 */

/* Source clock setting for PLL0 input clock (PLL0ISCSID1,PLL0ISCSID0) */
#define _CGC_PLL0_SOURCE_MAINOSC    ( 0x00000001UL )            /* Main OSC */
#define _CGC_PLL0_SOURCE_HSOSC      ( 0x00000002UL )            /* HS IntOSC */

/*
 *  PLL1 Enable Register (PLL1E)
 */

/* PLL1 disable trigger (PLL1DISTRG) */
#define _CGC_PLL1_STOP     ( 0x00000002UL )                     /* Stops PLL1 */
/* PLL1 enable trigger (PLL1ENTRG) */
#define _CGC_PLL1_START    ( 0x00000001UL )                     /* Starts PLL1 */

/*
 *  PLL1 Status Register (PLL1S)
 */

/* PLL1 active status (PLL1CLKACT) */
#define _CGC_PLL1_ACTIVE    ( 0x00000004UL )                    /* PLL1 is active */

/*
 *  PLL1 Input Clock Selection Register (CKSC_PLL1IS_CTL)
 */

/* Source clock setting for PLL1 input clock (PLL1ISCSID1,PLL1ISCSID0) */
#define _CGC_PLL1_SOURCE_MAINOSC    ( 0x00000001UL )            /* Main OSC */
#define _CGC_PLL1_SOURCE_HSOSC      ( 0x00000002UL )            /* HS IntOSC */

/*
 *  PLL1 Input Clock Active Register (CKSC_PLL1IS_ACT)
 */

/* Source clock for currently active PLL1 input clock (PLL1ISACT1,PLL1ISACT0) */
#define _CGC_PLL1_SOURCE_ACTIVE    ( 0x00000003UL )             /* Source clock for currently active PLL1
                                                                 * input clock */

/*
 *  PLL0 Input Clock Active Register (CKSC_PLL0IS_ACT)
 */

/* Source clock for currently active PLL0 input clock (PLL0ISACT1,PLL0ISACT0) */
#define _CGC_PLL0_SOURCE_ACTIVE    ( 0x00000003UL )             /* Source clock for currently active PLL0
                                                                 * input clock */

/*
 *  PPLLCLK Source Clock Selection Register (CKSC_PPLLCLKS_CTL)
 */

/* Source clock setting for PPLLCLK (PPLLCLKSCSID1,PPLLCLKSCSID0) */
#define _CGC_PPLLCLK_SOURCE_EMCLK      ( 0x00000001UL )         /* Emergency clock EMCLK */
#define _CGC_PPLLCLK_SOURCE_MAINOSC    ( 0x00000002UL )         /* MainOSC */
#define _CGC_PPLLCLK_SOURCE_PPLLOUT    ( 0x00000003UL )         /* PPLLOUT */

/*
 *  PPLLCLK Source Clock Active Register (CKSC_PPLLCLKS_ACT)
 */

/* Source clock for currently active PPLLCLK (PPLLCLKSACT1, PPLLCLKSACT0) */
#define _CGC_PPLLCLK_SOURCE_ACTIVE    ( 0x00000003UL )          /* Source clock for currently active PPLLCLK */

/*
 *  C_AWO_WDTA Clock Divider Selection Register (CKSC_AWDTAD_CTL)
 */

/* Clock divider setting for C_AWO_WDTA (AWDTADCSID1,AWDTADCSID0) */
#define _CGC_WDTA_CLK_SOURCE_LSOSC_128    ( 0x00000001UL )      /* LS IntOSC / 128 (default) */
#define _CGC_WDTA_CLK_SOURCE_LSOSC_1      ( 0x00000002UL )      /* LS IntOSC / 1 */

/*
 *  C_AWO_WDTA Stop Mask Register (CKSC_AWDTAD_STPM)
 */

/* C_AWO_WDTA stop request mask (AWDTADSTPMSK) */
#define _CGC_WDTA_CLK_REQUEST_STOP        ( 0x00000000UL )      /* C_AWO_WDTA is stopped in standby mode */
#define _CGC_WDTA_CLK_REQUEST_CONTINUE    ( 0x00000001UL )      /* C_AWO_WDTA is not stopped in standby mode */

/*
 *  C_AWO_TAUJ Source Clock Selection Register (CKSC_ATAUJS_CTL)
 */

/* Source clock setting for C_AWO_TAUJ (ATAUJSCSID2,ATAUJSCSID1,ATAUJSCSID0) */
#define _CGC_TAUJ_CLK_SOURCE_DISABLE     ( 0x00000000UL )       /* Disabled */
#define _CGC_TAUJ_CLK_SOURCE_HSOSC       ( 0x00000001UL )       /* HS IntOSC (default) */
#define _CGC_TAUJ_CLK_SOURCE_MAINOSC     ( 0x00000002UL )       /* MainOSC */
#define _CGC_TAUJ_CLK_SOURCE_LSOSC       ( 0x00000003UL )       /* LS IntOSC */
#define _CGC_TAUJ_CLK_SOURCE_PPLLCLK2    ( 0x00000004UL )       /* PPLLCLK2 */

/*
 *  C_AWO_TAUJ Clock Divider Selection Register (CKSC_ATAUJD_CTL)
 */

/* Clock divider setting for C_AWO_TAUJ (ATAUJDCSID2,ATAUJDCSID1,ATAUJDCSID0) */
#define _CGC_TAUJ_CLK_DIVIDER_1    ( 0x00000001UL )             /* CKSC_ATAUJS_CTL selection /1 (default) */
#define _CGC_TAUJ_CLK_DIVIDER_2    ( 0x00000002UL )             /* CKSC_ATAUJS_CTL selection /2 */
#define _CGC_TAUJ_CLK_DIVIDER_4    ( 0x00000003UL )             /* CKSC_ATAUJS_CTL selection /4 */
#define _CGC_TAUJ_CLK_DIVIDER_8    ( 0x00000004UL )             /* CKSC_ATAUJS_CTL selection /8 */

/*
 *  C_AWO_TAUJ Stop Mask Register (CKSC_ATAUJD_STPM)
 */

/* C_AWO_TAUJ stop request mask (ATAUJDSTPMSK) */
#define _CGC_TAUJ_CLK_REQUEST_STOP        ( 0x00000000UL )      /* C_AWO_TAUJ is stopped in standby mode */
#define _CGC_TAUJ_CLK_REQUEST_CONTINUE    ( 0x00000001UL )      /* C_AWO_TAUJ is not stopped in standby mode */

/*
 *  C_AWO_RTCA Source Clock Selection Register (CKSC_ARTCAS_CTL)
 */

/* Source clock setting for C_AWO_RTCA (ARTCASCSID1,ARTCASCSID0) */
#define _CGC_RTCA_CLK_SOURCE_DISABLE    ( 0x00000000UL )        /* Disabled(default) */
#define _CGC_RTCA_CLK_SOURCE_SUBOSC     ( 0x00000001UL )        /* SubOSC */
#define _CGC_RTCA_CLK_SOURCE_MAINOSC    ( 0x00000002UL )        /* MainOSC */
#define _CGC_RTCA_CLK_SOURCE_LSOSC      ( 0x00000003UL )        /* LS IntOSC */

/*
 *  C_AWO_RTCA Clock Divider Register (CKSC_ARTCAD_CTL)
 */

/* Clock divider setting for C_AWO_RTCA (ARTCADCSID2,ARTCADCSID1,ARTCADCSID0) */
#define _CGC_RTCA_CLK_DIVIDER_DISABLE    ( 0x00000000UL )       /* Disabled (default) */
#define _CGC_RTCA_CLK_DIVIDER_1          ( 0x00000001UL )       /* CKSC_ARTCAS_CTL selection /1 */
#define _CGC_RTCA_CLK_DIVIDER_2          ( 0x00000002UL )       /* CKSC_ARTCAS_CTL selection /2 */
#define _CGC_RTCA_CLK_DIVIDER_4          ( 0x00000003UL )       /* CKSC_ARTCAS_CTL selection /4 */
#define _CGC_RTCA_CLK_DIVIDER_8          ( 0x00000004UL )       /* CKSC_ARTCAS_CTL selection /8 */

/*
 *  C_AWO_RTCA Stop Mask Register (CKSC_ARTCAD_STPM)
 */

/* C_AWO_RTCA stop request mask (ARTCADSTPMSK) */
#define _CGC_RTCA_CLK_REQUEST_STOP        ( 0x00000000UL )      /* C_AWO_RTCA is stopped in standby mode */
#define _CGC_RTCA_CLK_REQUEST_CONTINUE    ( 0x00000001UL )      /* C_AWO_RTCA is not stopped in standby mode */

/*
 *  C_AWO_ADCA Source Clock Selection Register (CKSC_AADCAS_CTL)
 */

/* Source clock setting for C_AWO_ADCA (AADCASCSID1,AADCASCSID0) */
#define _CGC_ADCA0_CLK_SOURCE_DISABLE     ( 0x00000000UL )      /* Disabled */
#define _CGC_ADCA0_CLK_SOURCE_HSOSC       ( 0x00000001UL )      /* HS IntOSC (default) */
#define _CGC_ADCA0_CLK_SOURCE_MAINOSC     ( 0x00000002UL )      /* MainOSC */
#define _CGC_ADCA0_CLK_SOURCE_PPLLCLK2    ( 0x00000003UL )      /* PPLLCLK2 */

/*
 *  C_AWO_ADCA Clock Divider Selection Register (CKSC_AADCAD_CTL)
 */

/* Clock divider setting for C_AWO_ADCA (AADCADCSID1,AADCADCSID0) */
#define _CGC_ADCA0_CLK_DIVIDER_1    ( 0x00000001UL )            /* CKSC_AADCAS_CTL selection /1 (default) */
#define _CGC_ADCA0_CLK_DIVIDER_2    ( 0x00000002UL )            /* CKSC_AADCAS_CTL selection /2 */

/*
 *  C_AWO_ADCA Stop Mask Register (CKSC_AADCAD_STPM)
 */

/* C_AWO_ADCA stop request mask (AADCADSTPMSK) */
#define _CGC_ADCA0_CLK_REQUEST_STOP        ( 0x00000000UL )     /* C_AWO_ADCA is stopped in standby mode */
#define _CGC_ADCA0_CLK_REQUEST_CONTINUE    ( 0x00000001UL )     /* C_AWO_ADCA is not stopped in standby mode */

/*
 *  C_AWO_FOUT Source Clock Selection Register (CKSC_AFOUTS_CTL)
 */

/* Source clock setting for C_AWO_FOUT (AFOUTSCSID2,AFOUTSCSID1,AFOUTSCSID0) */
#define _CGC_FOUT_CLK_SOURCE_DISABLE     ( 0x00000000UL )       /* Disabled (default) */
#define _CGC_FOUT_CLK_SOURCE_MAINOSC     ( 0x00000001UL )       /* MainOSC */
#define _CGC_FOUT_CLK_SOURCE_HSOSC       ( 0x00000002UL )       /* HS IntOSC */
#define _CGC_FOUT_CLK_SOURCE_LSOSC       ( 0x00000003UL )       /* LS IntOSC */
#define _CGC_FOUT_CLK_SOURCE_SUBOSC      ( 0x00000004UL )       /* SubOSC */
#define _CGC_FOUT_CLK_SOURCE_PPLLCLK4    ( 0x00000005UL )       /* PPLLCLK4 */

/*
 *  C_AWO_FOUT Stop Mask Register (CKSC_AFOUTS_STPM)
 */

/* C_AWO_FOUT stop request mask (AFOUTSSTPMSK) */
#define _CGC_FOUT_CLK_REQUEST_STOP        ( 0x00000000UL )      /* C_AWO_FOUT is stopped in standby mode */
#define _CGC_FOUT_CLK_REQUEST_CONTINUE    ( 0x00000001UL )      /* C_AWO_FOUT is not stopped in standby mode */

/*
 *  C_ISO_CPUCLK Source Clock Selection Register (CKSC_CPUCLKS_CTL)
 */

/* Source clock setting for C_ISO_CPUCLK (CPUCLKSCSID1,CPUCLKSCSID0) */
#define _CGC_CPU_CLK_SOURCE_CPLL0OUT    ( 0x00000000UL )        /* CPLL0OUT */
#define _CGC_CPU_CLK_SOURCE_EMCLK       ( 0x00000001UL )        /* EMCLK (default) */
#define _CGC_CPU_CLK_SOURCE_MAINOSC     ( 0x00000002UL )        /* MainOSC */
#define _CGC_CPU_CLK_SOURCE_CPLL1OUT    ( 0x00000003UL )        /* CPLL1OUT */

/*
 *  C_ISO_CPUCLK Clock Divider Selection Register (CKSC_CPUCLKD_CTL)
 */

/* Clock divider CPLL1/0DIV setting (CPUCLKDPLL1,CPUCLKDPLL0) */
#define _CGC_CPLLOUT_DIVIDER_6    ( 0x00000000UL )              /* CPLL0/1OUT = VCO0/1OUT * 1/6 (80 MHz) (PLL0/1) */
#define _CGC_CPLLOUT_DIVIDER_4    ( 0x00000010UL )              /* CPLL0/1OUT = VCO0/1OUT * 1/4 (120 MHz) (PLL0/1) */
#define _CGC_CPLLOUT_DIVIDER_3    ( 0x00000030UL )              /* CPLL0OUT = VCO0OUT * 1/3 (160 MHz) (PLL0) */
#define _CGC_CPLLOUT_DIVIDER_2    ( 0x00000028UL )              /* CPLL0OUT = VCO0OUT * 1/2 (240 MHz) (PLL0) */
/* Clock divider setting for C_ISO_CPUCLK (CPUCLKDCSID2,CPUCLKDCSID1,CPUCLKDCSID0) */
#define _CGC_CPU_CLK_DIVIDER_1    ( 0x00000001UL )              /* CKSC_CPUCLKS_CTL selection /1 (Default) */
#define _CGC_CPU_CLK_DIVIDER_2    ( 0x00000002UL )              /* CKSC_CPUCLKS_CTL selection /2 */
#define _CGC_CPU_CLK_DIVIDER_4    ( 0x00000003UL )              /* CKSC_CPUCLKS_CTL selection /4 */
#define _CGC_CPU_CLK_DIVIDER_8    ( 0x00000004UL )              /* CKSC_CPUCLKS_CTL selection /8 */

/*
 *  C_ISO_PERI1 Source Clock Selection Register (CKSC_IPERI1S_CTL)
 */

/* Source clock setting for C_ISO_PERI1 (IPERI1SCSID1,IPERI1SCSID0) */
#define _CGC_PERI1_CLK_SOURCE_DISABLE    ( 0x00000000UL )       /* Disabled */
#define _CGC_PERI1_CLK_SOURCE_PPLLCLK    ( 0x00000001UL )       /* PPLLCLK (default) */

/*
 *  C_ISO_PERI2 Source Clock Selection Register (CKSC_IPERI2S_CTL)
 */

/* Source clock setting for C_ISO_PERI2 (IPERI2SCSID1,IPERI2SCSID0) */
#define _CGC_PERI2_CLK_SOURCE_DISABLE     ( 0x00000000UL )      /* Disabled */
#define _CGC_PERI2_CLK_SOURCE_PPLLCLK2    ( 0x00000001UL )      /* PPLLCLK2 (default) */

/*
 *  C_ISO_LIN Source Clock Selection Register (CKSC_ILINS_CTL)
 */

/* Source clock setting for C_ISO_LIN (ILINSCSID2,ILINSCSID1,ILINSCSID0) */
#define _CGC_RLIN_CLK_SOURCE_DISABLE     ( 0x00000000UL )       /* Disabled */
#define _CGC_RLIN_CLK_SOURCE_PPLLCLK2    ( 0x00000001UL )       /* PPLLCLK2 (default) */
#define _CGC_RLIN_CLK_SOURCE_MAINOSC     ( 0x00000002UL )       /* MainOSC */
#define _CGC_RLIN_CLK_SOURCE_HSOSC       ( 0x00000004UL )       /* HS IntOSC */

/*
 *  C_ISO_LIN Clock Divider Selection Register (CKSC_ILIND_CTL)
 */

/* Clock divider setting for C_ISO_LIN (ILINDCSID1,ILINDCSID0) */
#define _CGC_RLIN_CLK_DIVIDER_1    ( 0x00000001UL )             /* CKSC_ILINS_CTL selection /1 (default) */
#define _CGC_RLIN_CLK_DIVIDER_4    ( 0x00000002UL )             /* CKSC_ILINS_CTL selection /4 */
#define _CGC_RLIN_CLK_DIVIDER_8    ( 0x00000003UL )             /* CKSC_ILINS_CTL selection /8 */

/*
 *  C_ISO_LIN Stop Mask Register (CKSC_ILIND_STPM)
 */

/* C_AWO_FOUT stop request mask (ILINDSTPMSK) */
#define _CGC_RLIN_CLK_REQUEST_STOP        ( 0x00000000UL )      /* C_ISO_LIN is stopped in standby mode */
#define _CGC_RLIN_CLK_REQUEST_CONTINUE    ( 0x00000001UL )      /* C_ISO_LIN is not stopped in standby mode */

/*
 *  C_ISO_ADCA Source Clock Selection Register (CKSC_IADCAS_CTL)
 */

/* Source clock setting for C_ISO_ADCA (IADCASCSID1,IADCASCSID0) */
#define _CGC_ADCA1_CLK_SOURCE_DISABLE     ( 0x00000000UL )      /* Disabled */
#define _CGC_ADCA1_CLK_SOURCE_HSOSC       ( 0x00000001UL )      /* HS IntOSC (default) */
#define _CGC_ADCA1_CLK_SOURCE_MAINOSC     ( 0x00000002UL )      /* MainOSC */
#define _CGC_ADCA1_CLK_SOURCE_PPLLCLK2    ( 0x00000003UL )      /* PPLLCLK2 */

/*
 *  C_ISO_ADCA Clock Divider Selection Register (CKSC_IADCAD_CTL)
 */

/* Clock divider setting for C_ISO_ADCA (IADCADCSID1,IADCADCSID0) */
#define _CGC_ADCA1_CLK_DIVIDER_1    ( 0x00000001UL )            /* CKSC_IADCAS_CTL selection /1 (default) */
#define _CGC_ADCA1_CLK_DIVIDER_2    ( 0x00000002UL )            /* CKSC_IADCAS_CTL selection /2 */

/*
 *  C_ISO_CAN Source Clock Selection Register (CKSC_ICANS_CTL)
 */

/* Source clock setting for C_ISO_CAN (ICANSCSID1,ICANSCSID0) */
#define _CGC_RSCAN_CLK_SOURCE_DISABLE    ( 0x00000000UL )       /* Disabled */
#define _CGC_RSCAN_CLK_SOURCE_MAINOSC    ( 0x00000001UL )       /* MainOSC */
#define _CGC_RSCAN_CLK_SOURCE_PPLLCLK    ( 0x00000003UL )       /* PPLLCLK (default) */

/*
 *  C_ISO_CAN Stop Mask Register (CKSC_ICANS_STPM)
 */

/* C_ISO_CAN stop request mask (ICANSSTPMSK) */
#define _CGC_RSCAN_CLK_REQUEST_STOP        ( 0x00000000UL )     /* C_ISO_CAN is stopped in standby mode */
#define _CGC_RSCAN_CLK_REQUEST_CONTINUE    ( 0x00000001UL )     /* C_ISO_CAN is not stopped in standby mode */

/*
 *  C_ISO_CANOSC Clock Divider Selection Register (CKSC_ICANOSCD_CTL)
 */

/* Clock divider setting for C_ISO_CANOSC (ICANOSCDCSID1,ICANOSCDCSID0) */
#define _CGC_RSCANOSC_CLK_SOURCE_DISABLE     ( 0x00000000UL )   /* Disabled(default) */
#define _CGC_RSCANOSC_CLK_SOURCE_MAINOSC     ( 0x00000001UL )   /* MainOSC/1 */
#define _CGC_RSCANOSC_CLK_SOURCE_MAINOSC2    ( 0x00000002UL )   /* MainOSC/2 */

/*
 *  C_ISO_CANOSC Stop Mask Register (CKSC_ICANOSCD_STPM)
 */

/* C_ISO_CANOSC stop request mask (ICANOSCDSTPMSK) */
#define _CGC_RSCANOSC_CLK_REQUEST_STOP        ( 0x00000000UL )  /* C_ISO_CANOSC is stopped in standby mode */
#define _CGC_RSCANOSC_CLK_REQUEST_CONTINUE    ( 0x00000001UL )  /* C_ISO_CANOSC is not stopped in standby mode */

/*
 *  C_ISO_CSI Source Clock Selection Register (CKSC_ICSIS_CTL)
 */

/* Source clock setting for C_ISO_CSI (ICSISCSID2,ICSISCSID1,ICSISCSID0) */
#define _CGC_CSI_CLK_SOURCE_DISABLE    ( 0x00000000UL )         /* Disabled */
#define _CGC_CSI_CLK_SOURCE_PPLLCLK    ( 0x00000001UL )         /* PPLLCLK (default) */
#define _CGC_CSI_CLK_SOURCE_MAINOSC    ( 0x00000003UL )         /* Main OSC */
#define _CGC_CSI_CLK_SOURCE_HSOSC      ( 0x00000004UL )         /* HS IntOSC */

/*
 *  C_ISO_IIC Source Clock Selection Register (CKSC_IIICS_CTL)
 */

/* Source clock setting for C_ISO_IIC (IIICSCSID1,IIICSCSID0) */
#define _CGC_IIC_CLK_SOURCE_DISABLE              ( 0x00000000UL ) /* Disabled */
#define _CGC_IIC_CLK_SOURCE_PPLLCLK2             ( 0x00000001UL ) /* PPLLCLK2 (default) */

/***********************************************************************************************************************
* Macro definitions
***********************************************************************************************************************/
#define _CGC_MOSCC_DEFAULT_VALUE                 ( 0x00000004UL ) /* MOSCC default value */
#define _CGC_MOSCSTPM_DEFAULT_VALUE              ( 0x00000002UL ) /* MOSCSTPM default value */
#define _CGC_ROSCSTPM_DEFAULT_VALUE              ( 0x00000002UL ) /* ROSCSTPM default value */
#define _CGC_PLL1C_DEFAULT_VALUE                 ( 0x00010300UL ) /* PLL1C default value */
#define _CGC_PLL0C_DEFAULT_VALUE                 ( 0x60004000UL ) /* PLL0C default value */
#define _CGC_CKSC_AWDTAD_STPM_DEFAULT_VALUE      ( 0x00000002UL ) /* CKSC_AWDTAD_STPM default value */
#define _CGC_CKSC_ATAUJD_STPM_DEFAULT_VALUE      ( 0x00000002UL ) /* CKSC_ATAUJD_STPM default value */
#define _CGC_CKSC_ARTCAD_STPM_DEFAULT_VALUE      ( 0x00000002UL ) /* CKSC_ARTCAD_STPM default value */
#define _CGC_CKSC_AADCAD_STPM_DEFAULT_VALUE      ( 0x00000002UL ) /* CKSC_AADCAD_STPM default value */
#define _CGC_CKSC_AFOUTS_STPM_DEFAULT_VALUE      ( 0x00000002UL ) /* CKSC_AFOUTS_STPM default value */
#define _CGC_CKSC_ILIND_STPM_DEFAULT_VALUE       ( 0x00000002UL ) /* CKSC_ILIND_STPM default value */
#define _CGC_CKSC_ICANS_STPM_DEFAULT_VALUE       ( 0x00000002UL ) /* CKSC_ICANS_STPM default value */
#define _CGC_CKSC_ICANOSCD_STPM_DEFAULT_VALUE    ( 0x00000002UL ) /* CKSC_ICANOSCD_STPM default value */
#define _CGC_MAINOSC_STABILIZE_TIME              ( 0x000044C0UL ) /* Count value for the MainOSC stabilization counter */
#define _CGC_PLL1_DIVISION_RATIO                 ( 0x00000827UL ) /* PLL1 Division ratio Mr is set */
#define _CGC_FOUT_DIVISION_RATIO                 ( 0x00000001UL ) /* Clock divider N */
#define _CGC_PLL0_DIVISION_RATIO                 ( 0x00000827UL ) /* PLL0 Division ratio Mr is set */

/***********************************************************************************************************************
* Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Global functions
***********************************************************************************************************************/
void bsp_clock_init( void );

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif /* ifndef BSP_CLOCK_H */
