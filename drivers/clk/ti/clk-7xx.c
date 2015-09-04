/*
 * DRA7 Clock init
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo (t-kristo@ti.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk/ti.h>

#define DRA7_DPLL_ABE_DEFFREQ				180633600
#define DRA7_DPLL_GMAC_DEFFREQ				1000000000
#define DRA7_DPLL_USB_DEFFREQ				960000000


static struct ti_dt_clk dra7xx_clks[] = {
	DT_CLK(NULL, "atl_clkin0_ck", "atl_clkin0_ck"),
	DT_CLK(NULL, "atl_clkin1_ck", "atl_clkin1_ck"),
	DT_CLK(NULL, "atl_clkin2_ck", "atl_clkin2_ck"),
	DT_CLK(NULL, "atl_clkin3_ck", "atl_clkin3_ck"),
	DT_CLK(NULL, "hdmi_clkin_ck", "hdmi_clkin_ck"),
	DT_CLK(NULL, "mlb_clkin_ck", "mlb_clkin_ck"),
	DT_CLK(NULL, "mlbp_clkin_ck", "mlbp_clkin_ck"),
	DT_CLK(NULL, "pciesref_acs_clk_ck", "pciesref_acs_clk_ck"),
	DT_CLK(NULL, "ref_clkin0_ck", "ref_clkin0_ck"),
	DT_CLK(NULL, "ref_clkin1_ck", "ref_clkin1_ck"),
	DT_CLK(NULL, "ref_clkin2_ck", "ref_clkin2_ck"),
	DT_CLK(NULL, "ref_clkin3_ck", "ref_clkin3_ck"),
	DT_CLK(NULL, "rmii_clk_ck", "rmii_clk_ck"),
	DT_CLK(NULL, "sdvenc_clkin_ck", "sdvenc_clkin_ck"),
	DT_CLK(NULL, "secure_32k_clk_src_ck", "secure_32k_clk_src_ck"),
	DT_CLK(NULL, "sys_32k_ck", "sys_32k_ck"),
	DT_CLK(NULL, "virt_12000000_ck", "virt_12000000_ck"),
	DT_CLK(NULL, "virt_13000000_ck", "virt_13000000_ck"),
	DT_CLK(NULL, "virt_16800000_ck", "virt_16800000_ck"),
	DT_CLK(NULL, "virt_19200000_ck", "virt_19200000_ck"),
	DT_CLK(NULL, "virt_20000000_ck", "virt_20000000_ck"),
	DT_CLK(NULL, "virt_26000000_ck", "virt_26000000_ck"),
	DT_CLK(NULL, "virt_27000000_ck", "virt_27000000_ck"),
	DT_CLK(NULL, "virt_38400000_ck", "virt_38400000_ck"),
	DT_CLK(NULL, "sys_clkin1", "sys_clkin1"),
	DT_CLK(NULL, "sys_clkin2", "sys_clkin2"),
	DT_CLK(NULL, "usb_otg_clkin_ck", "usb_otg_clkin_ck"),
	DT_CLK(NULL, "video1_clkin_ck", "video1_clkin_ck"),
	DT_CLK(NULL, "video1_m2_clkin_ck", "video1_m2_clkin_ck"),
	DT_CLK(NULL, "video2_clkin_ck", "video2_clkin_ck"),
	DT_CLK(NULL, "video2_m2_clkin_ck", "video2_m2_clkin_ck"),
	DT_CLK(NULL, "abe_dpll_sys_clk_mux", "abe_dpll_sys_clk_mux"),
	DT_CLK(NULL, "abe_dpll_bypass_clk_mux", "abe_dpll_bypass_clk_mux"),
	DT_CLK(NULL, "abe_dpll_clk_mux", "abe_dpll_clk_mux"),
	DT_CLK(NULL, "dpll_abe_ck", "dpll_abe_ck"),
	DT_CLK(NULL, "dpll_abe_x2_ck", "dpll_abe_x2_ck"),
	DT_CLK(NULL, "dpll_abe_m2x2_ck", "dpll_abe_m2x2_ck"),
	DT_CLK(NULL, "abe_24m_fclk", "abe_24m_fclk"),
	DT_CLK(NULL, "abe_clk", "abe_clk"),
	DT_CLK(NULL, "aess_fclk", "aess_fclk"),
	DT_CLK(NULL, "abe_giclk_div", "abe_giclk_div"),
	DT_CLK(NULL, "abe_lp_clk_div", "abe_lp_clk_div"),
	DT_CLK(NULL, "abe_sys_clk_div", "abe_sys_clk_div"),
	DT_CLK(NULL, "adc_gfclk_mux", "adc_gfclk_mux"),
	DT_CLK(NULL, "dpll_pcie_ref_ck", "dpll_pcie_ref_ck"),
	DT_CLK(NULL, "dpll_pcie_ref_m2ldo_ck", "dpll_pcie_ref_m2ldo_ck"),
	DT_CLK(NULL, "apll_pcie_ck", "apll_pcie_ck"),
	DT_CLK(NULL, "apll_pcie_clkvcoldo", "apll_pcie_clkvcoldo"),
	DT_CLK(NULL, "apll_pcie_clkvcoldo_div", "apll_pcie_clkvcoldo_div"),
	DT_CLK(NULL, "apll_pcie_m2_ck", "apll_pcie_m2_ck"),
	DT_CLK(NULL, "sys_clk1_dclk_div", "sys_clk1_dclk_div"),
	DT_CLK(NULL, "sys_clk2_dclk_div", "sys_clk2_dclk_div"),
	DT_CLK(NULL, "dpll_abe_m2_ck", "dpll_abe_m2_ck"),
	DT_CLK(NULL, "per_abe_x1_dclk_div", "per_abe_x1_dclk_div"),
	DT_CLK(NULL, "dpll_abe_m3x2_ck", "dpll_abe_m3x2_ck"),
	DT_CLK(NULL, "dpll_core_ck", "dpll_core_ck"),
	DT_CLK(NULL, "dpll_core_x2_ck", "dpll_core_x2_ck"),
	DT_CLK(NULL, "dpll_core_h12x2_ck", "dpll_core_h12x2_ck"),
	DT_CLK(NULL, "mpu_dpll_hs_clk_div", "mpu_dpll_hs_clk_div"),
	DT_CLK(NULL, "dpll_mpu_ck", "dpll_mpu_ck"),
	DT_CLK(NULL, "dpll_mpu_m2_ck", "dpll_mpu_m2_ck"),
	DT_CLK(NULL, "mpu_dclk_div", "mpu_dclk_div"),
	DT_CLK(NULL, "dsp_dpll_hs_clk_div", "dsp_dpll_hs_clk_div"),
	DT_CLK(NULL, "dpll_dsp_ck", "dpll_dsp_ck"),
	DT_CLK(NULL, "dpll_dsp_m2_ck", "dpll_dsp_m2_ck"),
	DT_CLK(NULL, "dsp_gclk_div", "dsp_gclk_div"),
	DT_CLK(NULL, "iva_dpll_hs_clk_div", "iva_dpll_hs_clk_div"),
	DT_CLK(NULL, "dpll_iva_ck", "dpll_iva_ck"),
	DT_CLK(NULL, "dpll_iva_m2_ck", "dpll_iva_m2_ck"),
	DT_CLK(NULL, "iva_dclk", "iva_dclk"),
	DT_CLK(NULL, "dpll_gpu_ck", "dpll_gpu_ck"),
	DT_CLK(NULL, "dpll_gpu_m2_ck", "dpll_gpu_m2_ck"),
	DT_CLK(NULL, "gpu_dclk", "gpu_dclk"),
	DT_CLK(NULL, "dpll_core_m2_ck", "dpll_core_m2_ck"),
	DT_CLK(NULL, "core_dpll_out_dclk_div", "core_dpll_out_dclk_div"),
	DT_CLK(NULL, "dpll_ddr_ck", "dpll_ddr_ck"),
	DT_CLK(NULL, "dpll_ddr_m2_ck", "dpll_ddr_m2_ck"),
	DT_CLK(NULL, "emif_phy_dclk_div", "emif_phy_dclk_div"),
	DT_CLK(NULL, "dpll_gmac_ck", "dpll_gmac_ck"),
	DT_CLK(NULL, "dpll_gmac_m2_ck", "dpll_gmac_m2_ck"),
	DT_CLK(NULL, "gmac_250m_dclk_div", "gmac_250m_dclk_div"),
	DT_CLK(NULL, "video2_dclk_div", "video2_dclk_div"),
	DT_CLK(NULL, "video1_dclk_div", "video1_dclk_div"),
	DT_CLK(NULL, "hdmi_dclk_div", "hdmi_dclk_div"),
	DT_CLK(NULL, "per_dpll_hs_clk_div", "per_dpll_hs_clk_div"),
	DT_CLK(NULL, "dpll_per_ck", "dpll_per_ck"),
	DT_CLK(NULL, "dpll_per_m2_ck", "dpll_per_m2_ck"),
	DT_CLK(NULL, "func_96m_aon_dclk_div", "func_96m_aon_dclk_div"),
	DT_CLK(NULL, "usb_dpll_hs_clk_div", "usb_dpll_hs_clk_div"),
	DT_CLK(NULL, "dpll_usb_ck", "dpll_usb_ck"),
	DT_CLK(NULL, "dpll_usb_m2_ck", "dpll_usb_m2_ck"),
	DT_CLK(NULL, "l3init_480m_dclk_div", "l3init_480m_dclk_div"),
	DT_CLK(NULL, "usb_otg_dclk_div", "usb_otg_dclk_div"),
	DT_CLK(NULL, "sata_dclk_div", "sata_dclk_div"),
	DT_CLK(NULL, "dpll_pcie_ref_m2_ck", "dpll_pcie_ref_m2_ck"),
	DT_CLK(NULL, "pcie2_dclk_div", "pcie2_dclk_div"),
	DT_CLK(NULL, "pcie_dclk_div", "pcie_dclk_div"),
	DT_CLK(NULL, "emu_dclk_div", "emu_dclk_div"),
	DT_CLK(NULL, "secure_32k_dclk_div", "secure_32k_dclk_div"),
	DT_CLK(NULL, "eve_dpll_hs_clk_div", "eve_dpll_hs_clk_div"),
	DT_CLK(NULL, "dpll_eve_ck", "dpll_eve_ck"),
	DT_CLK(NULL, "dpll_eve_m2_ck", "dpll_eve_m2_ck"),
	DT_CLK(NULL, "eve_dclk_div", "eve_dclk_div"),
	DT_CLK(NULL, "clkoutmux0_clk_mux", "clkoutmux0_clk_mux"),
	DT_CLK(NULL, "clkoutmux1_clk_mux", "clkoutmux1_clk_mux"),
	DT_CLK(NULL, "clkoutmux2_clk_mux", "clkoutmux2_clk_mux"),
	DT_CLK(NULL, "custefuse_sys_gfclk_div", "custefuse_sys_gfclk_div"),
	DT_CLK(NULL, "dpll_core_h13x2_ck", "dpll_core_h13x2_ck"),
	DT_CLK(NULL, "dpll_core_h14x2_ck", "dpll_core_h14x2_ck"),
	DT_CLK(NULL, "dpll_core_h22x2_ck", "dpll_core_h22x2_ck"),
	DT_CLK(NULL, "dpll_core_h23x2_ck", "dpll_core_h23x2_ck"),
	DT_CLK(NULL, "dpll_core_h24x2_ck", "dpll_core_h24x2_ck"),
	DT_CLK(NULL, "dpll_ddr_x2_ck", "dpll_ddr_x2_ck"),
	DT_CLK(NULL, "dpll_ddr_h11x2_ck", "dpll_ddr_h11x2_ck"),
	DT_CLK(NULL, "dpll_dsp_x2_ck", "dpll_dsp_x2_ck"),
	DT_CLK(NULL, "dpll_dsp_m3x2_ck", "dpll_dsp_m3x2_ck"),
	DT_CLK(NULL, "dpll_gmac_x2_ck", "dpll_gmac_x2_ck"),
	DT_CLK(NULL, "dpll_gmac_h11x2_ck", "dpll_gmac_h11x2_ck"),
	DT_CLK(NULL, "dpll_gmac_h12x2_ck", "dpll_gmac_h12x2_ck"),
	DT_CLK(NULL, "dpll_gmac_h13x2_ck", "dpll_gmac_h13x2_ck"),
	DT_CLK(NULL, "dpll_gmac_m3x2_ck", "dpll_gmac_m3x2_ck"),
	DT_CLK(NULL, "dpll_per_x2_ck", "dpll_per_x2_ck"),
	DT_CLK(NULL, "dpll_per_h11x2_ck", "dpll_per_h11x2_ck"),
	DT_CLK(NULL, "dpll_per_h12x2_ck", "dpll_per_h12x2_ck"),
	DT_CLK(NULL, "dpll_per_h13x2_ck", "dpll_per_h13x2_ck"),
	DT_CLK(NULL, "dpll_per_h14x2_ck", "dpll_per_h14x2_ck"),
	DT_CLK(NULL, "dpll_per_m2x2_ck", "dpll_per_m2x2_ck"),
	DT_CLK(NULL, "dpll_usb_clkdcoldo", "dpll_usb_clkdcoldo"),
	DT_CLK(NULL, "eve_clk", "eve_clk"),
	DT_CLK(NULL, "func_128m_clk", "func_128m_clk"),
	DT_CLK(NULL, "func_12m_fclk", "func_12m_fclk"),
	DT_CLK(NULL, "func_24m_clk", "func_24m_clk"),
	DT_CLK(NULL, "func_48m_fclk", "func_48m_fclk"),
	DT_CLK(NULL, "func_96m_fclk", "func_96m_fclk"),
	DT_CLK(NULL, "gmii_m_clk_div", "gmii_m_clk_div"),
	DT_CLK(NULL, "hdmi_clk2_div", "hdmi_clk2_div"),
	DT_CLK(NULL, "hdmi_div_clk", "hdmi_div_clk"),
	DT_CLK(NULL, "hdmi_dpll_clk_mux", "hdmi_dpll_clk_mux"),
	DT_CLK(NULL, "l3_iclk_div", "l3_iclk_div"),
	DT_CLK(NULL, "l3init_60m_fclk", "l3init_60m_fclk"),
	DT_CLK(NULL, "l4_root_clk_div", "l4_root_clk_div"),
	DT_CLK(NULL, "mlb_clk", "mlb_clk"),
	DT_CLK(NULL, "mlbp_clk", "mlbp_clk"),
	DT_CLK(NULL, "per_abe_x1_gfclk2_div", "per_abe_x1_gfclk2_div"),
	DT_CLK(NULL, "timer_sys_clk_div", "timer_sys_clk_div"),
	DT_CLK(NULL, "video1_clk2_div", "video1_clk2_div"),
	DT_CLK(NULL, "video1_div_clk", "video1_div_clk"),
	DT_CLK(NULL, "video1_dpll_clk_mux", "video1_dpll_clk_mux"),
	DT_CLK(NULL, "video2_clk2_div", "video2_clk2_div"),
	DT_CLK(NULL, "video2_div_clk", "video2_div_clk"),
	DT_CLK(NULL, "video2_dpll_clk_mux", "video2_dpll_clk_mux"),
	DT_CLK(NULL, "wkupaon_iclk_mux", "wkupaon_iclk_mux"),
	DT_CLK(NULL, "dss_32khz_clk", "dss_32khz_clk"),
	DT_CLK(NULL, "dss_48mhz_clk", "dss_48mhz_clk"),
	DT_CLK(NULL, "dss_dss_clk", "dss_dss_clk"),
	DT_CLK(NULL, "dss_hdmi_clk", "dss_hdmi_clk"),
	DT_CLK(NULL, "dss_video1_clk", "dss_video1_clk"),
	DT_CLK(NULL, "dss_video2_clk", "dss_video2_clk"),
	DT_CLK(NULL, "gpio1_dbclk", "gpio1_dbclk"),
	DT_CLK(NULL, "gpio2_dbclk", "gpio2_dbclk"),
	DT_CLK(NULL, "gpio3_dbclk", "gpio3_dbclk"),
	DT_CLK(NULL, "gpio4_dbclk", "gpio4_dbclk"),
	DT_CLK(NULL, "gpio5_dbclk", "gpio5_dbclk"),
	DT_CLK(NULL, "gpio6_dbclk", "gpio6_dbclk"),
	DT_CLK(NULL, "gpio7_dbclk", "gpio7_dbclk"),
	DT_CLK(NULL, "gpio8_dbclk", "gpio8_dbclk"),
	DT_CLK(NULL, "mmc1_clk32k", "mmc1_clk32k"),
	DT_CLK(NULL, "mmc2_clk32k", "mmc2_clk32k"),
	DT_CLK(NULL, "mmc3_clk32k", "mmc3_clk32k"),
	DT_CLK(NULL, "mmc4_clk32k", "mmc4_clk32k"),
	DT_CLK(NULL, "sata_ref_clk", "sata_ref_clk"),
	DT_CLK(NULL, "usb_otg_ss1_refclk960m", "usb_otg_ss1_refclk960m"),
	DT_CLK(NULL, "usb_otg_ss2_refclk960m", "usb_otg_ss2_refclk960m"),
	DT_CLK(NULL, "usb_phy1_always_on_clk32k", "usb_phy1_always_on_clk32k"),
	DT_CLK(NULL, "usb_phy2_always_on_clk32k", "usb_phy2_always_on_clk32k"),
	DT_CLK(NULL, "usb_phy3_always_on_clk32k", "usb_phy3_always_on_clk32k"),
	DT_CLK(NULL, "atl_dpll_clk_mux", "atl_dpll_clk_mux"),
	DT_CLK(NULL, "atl_gfclk_mux", "atl_gfclk_mux"),
	DT_CLK(NULL, "dcan1_sys_clk_mux", "dcan1_sys_clk_mux"),
	DT_CLK(NULL, "gmac_gmii_ref_clk_div", "gmac_gmii_ref_clk_div"),
	DT_CLK(NULL, "gmac_rft_clk_mux", "gmac_rft_clk_mux"),
	DT_CLK(NULL, "gpu_core_gclk_mux", "gpu_core_gclk_mux"),
	DT_CLK(NULL, "gpu_hyd_gclk_mux", "gpu_hyd_gclk_mux"),
	DT_CLK(NULL, "ipu1_gfclk_mux", "ipu1_gfclk_mux"),
	DT_CLK(NULL, "l3instr_ts_gclk_div", "l3instr_ts_gclk_div"),
	DT_CLK(NULL, "mcasp1_ahclkr_mux", "mcasp1_ahclkr_mux"),
	DT_CLK(NULL, "mcasp1_ahclkx_mux", "mcasp1_ahclkx_mux"),
	DT_CLK(NULL, "mcasp1_aux_gfclk_mux", "mcasp1_aux_gfclk_mux"),
	DT_CLK(NULL, "mcasp2_ahclkr_mux", "mcasp2_ahclkr_mux"),
	DT_CLK(NULL, "mcasp2_ahclkx_mux", "mcasp2_ahclkx_mux"),
	DT_CLK(NULL, "mcasp2_aux_gfclk_mux", "mcasp2_aux_gfclk_mux"),
	DT_CLK(NULL, "mcasp3_ahclkx_mux", "mcasp3_ahclkx_mux"),
	DT_CLK(NULL, "mcasp3_aux_gfclk_mux", "mcasp3_aux_gfclk_mux"),
	DT_CLK(NULL, "mcasp4_ahclkx_mux", "mcasp4_ahclkx_mux"),
	DT_CLK(NULL, "mcasp4_aux_gfclk_mux", "mcasp4_aux_gfclk_mux"),
	DT_CLK(NULL, "mcasp5_ahclkx_mux", "mcasp5_ahclkx_mux"),
	DT_CLK(NULL, "mcasp5_aux_gfclk_mux", "mcasp5_aux_gfclk_mux"),
	DT_CLK(NULL, "mcasp6_ahclkx_mux", "mcasp6_ahclkx_mux"),
	DT_CLK(NULL, "mcasp6_aux_gfclk_mux", "mcasp6_aux_gfclk_mux"),
	DT_CLK(NULL, "mcasp7_ahclkx_mux", "mcasp7_ahclkx_mux"),
	DT_CLK(NULL, "mcasp7_aux_gfclk_mux", "mcasp7_aux_gfclk_mux"),
	DT_CLK(NULL, "mcasp8_ahclk_mux", "mcasp8_ahclk_mux"),
	DT_CLK(NULL, "mcasp8_aux_gfclk_mux", "mcasp8_aux_gfclk_mux"),
	DT_CLK(NULL, "mmc1_fclk_mux", "mmc1_fclk_mux"),
	DT_CLK(NULL, "mmc1_fclk_div", "mmc1_fclk_div"),
	DT_CLK(NULL, "mmc2_fclk_mux", "mmc2_fclk_mux"),
	DT_CLK(NULL, "mmc2_fclk_div", "mmc2_fclk_div"),
	DT_CLK(NULL, "mmc3_gfclk_mux", "mmc3_gfclk_mux"),
	DT_CLK(NULL, "mmc3_gfclk_div", "mmc3_gfclk_div"),
	DT_CLK(NULL, "mmc4_gfclk_mux", "mmc4_gfclk_mux"),
	DT_CLK(NULL, "mmc4_gfclk_div", "mmc4_gfclk_div"),
	DT_CLK(NULL, "qspi_gfclk_mux", "qspi_gfclk_mux"),
	DT_CLK(NULL, "qspi_gfclk_div", "qspi_gfclk_div"),
	DT_CLK(NULL, "timer10_gfclk_mux", "timer10_gfclk_mux"),
	DT_CLK(NULL, "timer11_gfclk_mux", "timer11_gfclk_mux"),
	DT_CLK(NULL, "timer13_gfclk_mux", "timer13_gfclk_mux"),
	DT_CLK(NULL, "timer14_gfclk_mux", "timer14_gfclk_mux"),
	DT_CLK(NULL, "timer15_gfclk_mux", "timer15_gfclk_mux"),
	DT_CLK(NULL, "timer16_gfclk_mux", "timer16_gfclk_mux"),
	DT_CLK(NULL, "timer1_gfclk_mux", "timer1_gfclk_mux"),
	DT_CLK(NULL, "timer2_gfclk_mux", "timer2_gfclk_mux"),
	DT_CLK(NULL, "timer3_gfclk_mux", "timer3_gfclk_mux"),
	DT_CLK(NULL, "timer4_gfclk_mux", "timer4_gfclk_mux"),
	DT_CLK(NULL, "timer5_gfclk_mux", "timer5_gfclk_mux"),
	DT_CLK(NULL, "timer6_gfclk_mux", "timer6_gfclk_mux"),
	DT_CLK(NULL, "timer7_gfclk_mux", "timer7_gfclk_mux"),
	DT_CLK(NULL, "timer8_gfclk_mux", "timer8_gfclk_mux"),
	DT_CLK(NULL, "timer9_gfclk_mux", "timer9_gfclk_mux"),
	DT_CLK(NULL, "uart10_gfclk_mux", "uart10_gfclk_mux"),
	DT_CLK(NULL, "uart1_gfclk_mux", "uart1_gfclk_mux"),
	DT_CLK(NULL, "uart2_gfclk_mux", "uart2_gfclk_mux"),
	DT_CLK(NULL, "uart3_gfclk_mux", "uart3_gfclk_mux"),
	DT_CLK(NULL, "uart4_gfclk_mux", "uart4_gfclk_mux"),
	DT_CLK(NULL, "uart5_gfclk_mux", "uart5_gfclk_mux"),
	DT_CLK(NULL, "uart6_gfclk_mux", "uart6_gfclk_mux"),
	DT_CLK(NULL, "uart7_gfclk_mux", "uart7_gfclk_mux"),
	DT_CLK(NULL, "uart8_gfclk_mux", "uart8_gfclk_mux"),
	DT_CLK(NULL, "uart9_gfclk_mux", "uart9_gfclk_mux"),
	DT_CLK(NULL, "vip1_gclk_mux", "vip1_gclk_mux"),
	DT_CLK(NULL, "vip2_gclk_mux", "vip2_gclk_mux"),
	DT_CLK(NULL, "vip3_gclk_mux", "vip3_gclk_mux"),
	DT_CLK("omap_i2c.1", "ick", "dummy_ck"),
	DT_CLK("omap_i2c.2", "ick", "dummy_ck"),
	DT_CLK("omap_i2c.3", "ick", "dummy_ck"),
	DT_CLK("omap_i2c.4", "ick", "dummy_ck"),
	DT_CLK(NULL, "mailboxes_ick", "dummy_ck"),
	DT_CLK("omap_hsmmc.0", "ick", "dummy_ck"),
	DT_CLK("omap_hsmmc.1", "ick", "dummy_ck"),
	DT_CLK("omap_hsmmc.2", "ick", "dummy_ck"),
	DT_CLK("omap_hsmmc.3", "ick", "dummy_ck"),
	DT_CLK("omap_hsmmc.4", "ick", "dummy_ck"),
	DT_CLK("omap-mcbsp.1", "ick", "dummy_ck"),
	DT_CLK("omap-mcbsp.2", "ick", "dummy_ck"),
	DT_CLK("omap-mcbsp.3", "ick", "dummy_ck"),
	DT_CLK("omap-mcbsp.4", "ick", "dummy_ck"),
	DT_CLK("omap2_mcspi.1", "ick", "dummy_ck"),
	DT_CLK("omap2_mcspi.2", "ick", "dummy_ck"),
	DT_CLK("omap2_mcspi.3", "ick", "dummy_ck"),
	DT_CLK("omap2_mcspi.4", "ick", "dummy_ck"),
	DT_CLK(NULL, "uart1_ick", "dummy_ck"),
	DT_CLK(NULL, "uart2_ick", "dummy_ck"),
	DT_CLK(NULL, "uart3_ick", "dummy_ck"),
	DT_CLK(NULL, "uart4_ick", "dummy_ck"),
	DT_CLK("usbhs_omap", "usbhost_ick", "dummy_ck"),
	DT_CLK("usbhs_omap", "usbtll_fck", "dummy_ck"),
	DT_CLK("omap_wdt", "ick", "dummy_ck"),
	DT_CLK(NULL, "timer_32k_ck", "sys_32k_ck"),
	DT_CLK("4ae18000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48032000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48034000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48036000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("4803e000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48086000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48088000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48820000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48822000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48824000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48826000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("48828000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("4882a000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("4882c000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK("4882e000.timer", "timer_sys_ck", "timer_sys_clk_div"),
	DT_CLK(NULL, "sys_clkin", "sys_clkin1"),
	DT_CLK(NULL, "dss_deshdcp_clk", "dss_deshdcp_clk"),
	{ .node_name = NULL },
};

int __init dra7xx_dt_clk_init(void)
{
	int rc;
	struct clk *abe_dpll_mux, *sys_clkin2, *dpll_ck, *hdcp_ck;

	ti_dt_clocks_register(dra7xx_clks);

	omap2_clk_disable_autoidle_all();

	abe_dpll_mux = clk_get_sys(NULL, "abe_dpll_sys_clk_mux");
	sys_clkin2 = clk_get_sys(NULL, "sys_clkin2");
	dpll_ck = clk_get_sys(NULL, "dpll_abe_ck");

	rc = clk_set_parent(abe_dpll_mux, sys_clkin2);
	if (!rc)
		rc = clk_set_rate(dpll_ck, DRA7_DPLL_ABE_DEFFREQ);
	if (rc)
		pr_err("%s: failed to configure ABE DPLL!\n", __func__);

	dpll_ck = clk_get_sys(NULL, "dpll_abe_m2x2_ck");
	rc = clk_set_rate(dpll_ck, DRA7_DPLL_ABE_DEFFREQ * 2);
	if (rc)
		pr_err("%s: failed to configure ABE DPLL m2x2!\n", __func__);

	dpll_ck = clk_get_sys(NULL, "dpll_gmac_ck");
	rc = clk_set_rate(dpll_ck, DRA7_DPLL_GMAC_DEFFREQ);
	if (rc)
		pr_err("%s: failed to configure GMAC DPLL!\n", __func__);

	dpll_ck = clk_get_sys(NULL, "dpll_usb_ck");
	rc = clk_set_rate(dpll_ck, DRA7_DPLL_USB_DEFFREQ);
	if (rc)
		pr_err("%s: failed to configure USB DPLL!\n", __func__);

	dpll_ck = clk_get_sys(NULL, "dpll_usb_m2_ck");
	rc = clk_set_rate(dpll_ck, DRA7_DPLL_USB_DEFFREQ/2);
	if (rc)
		pr_err("%s: failed to set USB_DPLL M2 OUT\n", __func__);

	hdcp_ck = clk_get_sys(NULL, "dss_deshdcp_clk");
	rc = clk_prepare_enable(hdcp_ck);
	if (rc)
		pr_err("%s: failed to set dss_deshdcp_clk\n", __func__);

	return rc;
}
