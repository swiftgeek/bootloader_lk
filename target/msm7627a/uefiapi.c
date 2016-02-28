#include <err.h>
#include <debug.h>
#include <stdint.h>
#include <mmc.h>
#include <board.h>
#include <target.h>
#include <dev/keys.h>
#include <dev/ssbi.h>
#include <dev/fbcon.h>
#include <mipi_dsi.h>
#include <target/display.h>
#include <platform/iomap.h>
#include <platform/timer.h>
#include <partition_parser.h>
#include <uefiapi.h>

/////////////////////////////////////////////////////////////////////////
//                                KEYS                                 //
/////////////////////////////////////////////////////////////////////////

static int target_power_key(void)
{
	uint8_t ret = 0;

//	pm8921_pwrkey_status(&ret);
	return ret;
}

static int event_source_poll(key_event_source_t* source) {
	uint16_t value = target_power_key();
	if(keys_set_report_key(source, 0, value)){
		keys_post_event(13, value);
	}

	return NO_ERROR;
}

static key_event_source_t event_source = {
	.poll = event_source_poll
};

/////////////////////////////////////////////////////////////////////////
//                            PLATFORM                                 //
/////////////////////////////////////////////////////////////////////////

void msm_clocks_init(void);
void platform_init_timer(void);
void keypad_init(void);

void api_platform_early_init(void) {
// from platform_early_init (platform.c), but without VIC
// UART
#if WITH_DEBUG_UART
	uart1_clock_init();
	uart_init();
#endif
	platform_init_timer();
}

void api_platform_init(void) {
// from target_init (init.c)
// Keys - apparently NOT for NAND boot!
//	keys_init();
//	keypad_init();
// Wait for AMSS boot before booting from eMMC
//  while (readl(MSM_SHARED_BASE + 0x14) != 1) ;
//	if (!(dev = mmc_boot_main(MMC_SLOT, MSM_SDC3_BASE))) {
//		dprintf(CRITICAL, "mmc init failed!");
//		ASSERT(0);
//	}
  //return happens here for eMMC boot
}

/////////////////////////////////////////////////////////////////////////
//                            BlockIO                                  //
/////////////////////////////////////////////////////////////////////////
// mmc_sdhci.c

extern char sn_buf[13];

static unsigned mmc_sdc_base[] =
    { MSM_SDC1_BASE, MSM_SDC3_BASE };

int api_mmc_init(lkapi_biodev_t* dev) {
//	unsigned base_addr;
//	unsigned char slot;
//	static int initialized = 0;
//
//	if(initialized)
//		goto out;
//
//	/* Trying Slot 1 first */
//	slot = 1;
//	base_addr = mmc_sdc_base[slot - 1];
//	if (mmc_boot_main(slot, base_addr)) {
//		/* Trying Slot 3 next */
//		slot = 3;
//		base_addr = mmc_sdc_base[slot - 1];
//		if (mmc_boot_main(slot, base_addr)) {
//			dprintf(CRITICAL, "mmc init failed!");
//			ASSERT(0);
//		}
//	}
//
//	target_serialno((unsigned char *) sn_buf);
//	dprintf(SPEW,"serial number: %s\n",sn_buf);
//
//	initialized = 1;
//
//out:
//	if(dev)
//		dev->num_blocks = mmc_get_device_capacity()/dev->block_size;
	return 0;
}
