/* linux/arch/arm/mach-exynos4/dev-spi.c
 *
 * Copyright (C) 2011 Samsung Electronics Co. Ltd.
 *	Jaswinder Singh <jassi.brar@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/gpio.h>

#include <mach/dma.h>
#include <mach/map.h>
#include <mach/irqs.h>
#include <mach/spi-clocks.h>

#include <plat/s3c64xx-spi.h>
#include <plat/gpio-cfg.h>

static char *spi_src_clks[] = {
	[EXYNOS4_SPI_SRCCLK_SCLK] = "sclk_spi",
};

/* SPI Controller platform_devices */

/* Since we emulate multi-cs capability, we do not touch the CS.
 * The emulated CS is toggled by board specific mechanism, as it can
 * be either some immediate GPIO or some signal out of some other
 * chip in between ... or some yet another way.
 * We simply do not assume anything about CS.
 */
static int exynos4_spi_cfg_gpio(struct platform_device *pdev)
{
	switch (pdev->id) {
	case 0:
		s3c_gpio_cfgpin(EXYNOS4_GPB(0), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPB(0), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgall_range(EXYNOS4_GPB(2), 2,
				      S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);
		break;

	case 1:
		s3c_gpio_cfgpin(EXYNOS4_GPB(4), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPB(4), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgall_range(EXYNOS4_GPB(6), 2,
				      S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);
		break;

	case 2:
		s3c_gpio_cfgpin(EXYNOS4_GPC1(1), S3C_GPIO_SFN(5));
		s3c_gpio_setpull(EXYNOS4_GPC1(1), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgall_range(EXYNOS4_GPC1(3), 2,
				      S3C_GPIO_SFN(5), S3C_GPIO_PULL_UP);
		break;

	default:
		dev_err(&pdev->dev, "Invalid SPI Controller number!");
		return -EINVAL;
	}

	return 0;
}

static struct resource exynos4_spi0_resource[] = {
	[0] = {
		.start = EXYNOS4_PA_SPI0,
		.end   = EXYNOS4_PA_SPI0 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_SPI0_TX,
		.end   = DMACH_SPI0_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_SPI0_RX,
		.end   = DMACH_SPI0_RX,
		.flags = IORESOURCE_DMA,
	},
	[3] = {
		.start = IRQ_SPI0,
		.end   = IRQ_SPI0,
		.flags = IORESOURCE_IRQ,
	},
};

static struct s3c64xx_spi_info exynos4_spi0_pdata = {
	.cfg_gpio = exynos4_spi_cfg_gpio,
	.fifo_lvl_mask = 0x1ff,
	.rx_lvl_offset = 15,
	.high_speed = 1,
	.clk_from_cmu = true,
};

static u64 spi_dmamask = DMA_BIT_MASK(32);

struct platform_device exynos4_device_spi0 = {
	.name		  = "s3c64xx-spi",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(exynos4_spi0_resource),
	.resource	  = exynos4_spi0_resource,
	.dev = {
		.dma_mask		= &spi_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data = &exynos4_spi0_pdata,
	},
};

static struct resource exynos4_spi1_resource[] = {
	[0] = {
		.start = EXYNOS4_PA_SPI1,
		.end   = EXYNOS4_PA_SPI1 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_SPI1_TX,
		.end   = DMACH_SPI1_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_SPI1_RX,
		.end   = DMACH_SPI1_RX,
		.flags = IORESOURCE_DMA,
	},
	[3] = {
		.start = IRQ_SPI1,
		.end   = IRQ_SPI1,
		.flags = IORESOURCE_IRQ,
	},
};

static struct s3c64xx_spi_info exynos4_spi1_pdata = {
	.cfg_gpio = exynos4_spi_cfg_gpio,
	.fifo_lvl_mask = 0x7f,
	.rx_lvl_offset = 15,
	.high_speed = 1,
	.clk_from_cmu = true,
};

struct platform_device exynos4_device_spi1 = {
	.name		  = "s3c64xx-spi",
	.id		  = 1,
	.num_resources	  = ARRAY_SIZE(exynos4_spi1_resource),
	.resource	  = exynos4_spi1_resource,
	.dev = {
		.dma_mask		= &spi_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data = &exynos4_spi1_pdata,
	},
};

static struct resource exynos4_spi2_resource[] = {
	[0] = {
		.start = EXYNOS4_PA_SPI2,
		.end   = EXYNOS4_PA_SPI2 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_SPI2_TX,
		.end   = DMACH_SPI2_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_SPI2_RX,
		.end   = DMACH_SPI2_RX,
		.flags = IORESOURCE_DMA,
	},
	[3] = {
		.start = IRQ_SPI2,
		.end   = IRQ_SPI2,
		.flags = IORESOURCE_IRQ,
	},
};

static struct s3c64xx_spi_info exynos4_spi2_pdata = {
	.cfg_gpio = exynos4_spi_cfg_gpio,
	.fifo_lvl_mask = 0x7f,
	.rx_lvl_offset = 15,
	.high_speed = 1,
	.clk_from_cmu = true,
};

struct platform_device exynos4_device_spi2 = {
	.name		  = "s3c64xx-spi",
	.id		  = 2,
	.num_resources	  = ARRAY_SIZE(exynos4_spi2_resource),
	.resource	  = exynos4_spi2_resource,
	.dev = {
		.dma_mask		= &spi_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data = &exynos4_spi2_pdata,
	},
};

void __init exynos4_spi_set_info(int cntrlr, int src_clk_nr, int num_cs)
{
	struct s3c64xx_spi_info *pd;

	/* Reject invalid configuration */
	if (!num_cs || src_clk_nr < 0
			|| src_clk_nr > EXYNOS4_SPI_SRCCLK_SCLK) {
		printk(KERN_ERR "%s: Invalid SPI configuration\n", __func__);
		return;
	}

	switch (cntrlr) {
	case 0:
		pd = &exynos4_spi0_pdata;
		break;
	case 1:
		pd = &exynos4_spi1_pdata;
		break;
	case 2:
		pd = &exynos4_spi2_pdata;
		break;
	default:
		printk(KERN_ERR "%s: Invalid SPI controller(%d)\n",
							__func__, cntrlr);
		return;
	}

	pd->num_cs = num_cs;
	pd->src_clk_nr = src_clk_nr;
	pd->src_clk_name = spi_src_clks[src_clk_nr];
}
