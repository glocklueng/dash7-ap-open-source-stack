/*
 *  Created on: Feb 2, 2013
 *  Authors:
 * 		maarten.weyn@artesis.be
 */


#include <string.h>
#include <nwl/nwl.h>
#include <hal/system.h>
#include <hal/button.h>
#include <hal/leds.h>
#include <hal/rtc.h>
#include <log.h>
#include <timer.h>


dll_channel_scan_t scan_cfg1 = {
		0x10,
		FrameTypeBackgroundFrame,
		20,
		500
};

dll_channel_scan_series_t scan_series_cfg;
uint8_t foreground_channel_id;

void scan_foreground_frame(void* arg)
{
	dll_foreground_scan();
}

void rx_callback(nwl_rx_res_t* rx_res)
{
	log_print_string("RX CB");
	if (rx_res->frame_type == FrameTypeBackgroundFrame)
	{
		led_toggle(3);

		nwl_background_frame_t* frame = (nwl_background_frame_t*) rx_res->frame;
		if (frame->bpid == BPID_AdvP)
		{
			AdvP_Data* data = (AdvP_Data*) frame->protocol_data;
			log_print_string("AdvP_Data");
			log_print_data(data->eta, 2);

			timer_event event;
			event.next_event = *((uint16_t*)data->eta);
			foreground_channel_id = data->channel_id;
			dll_set_foreground_scan_detection_timeout(200);
			dll_set_scan_spectrum_id(data->channel_id);
			event.f = &scan_foreground_frame;

			timer_add_event(&event);
		}



	} else {
		led_toggle(2);
	}
}

start_rx()
{
	led_on(3);
	dll_channel_scan_series(&scan_series_cfg);
}


void main(void) {
	system_init();
	//button_enable_interrupts();

	nwl_init();
	//nwl_set_tx_callback(&tx_callback);
	nwl_set_rx_callback(&rx_callback);

	dll_channel_scan_t scan_confgs[1];
	scan_confgs[0] = scan_cfg1;

	scan_series_cfg.length = 0;
	scan_series_cfg.values = scan_confgs;

	log_print_string("started");


	start_rx();

	while(1)
	{
		system_lowpower_mode(4,1);
	}
}


#pragma vector=ADC12_VECTOR,AES_VECTOR,COMP_B_VECTOR,DMA_VECTOR,PORT1_VECTOR,PORT2_VECTOR,RTC_VECTOR,SYSNMI_VECTOR,UNMI_VECTOR,USCI_A0_VECTOR,USCI_B0_VECTOR,WDT_VECTOR,TIMER0_A1_VECTOR,TIMER0_A0_VECTOR,TIMER1_A1_VECTOR
__interrupt void ISR_trap(void)
{
  /* For debugging purposes, you can trap the CPU & code execution here with an
     infinite loop */
  //while (1);
	__no_operation();

  /* If a reset is preferred, in scenarios where you want to reset the entire system and
     restart the application from the beginning, use one of the following lines depending
     on your MSP430 device family, and make sure to comment out the while (1) line above */

  /* If you are using MSP430F5xx or MSP430F6xx devices, use the following line
     to trigger a software BOR.   */
  PMMCTL0 = PMMPW | PMMSWBOR;          // Apply PMM password and trigger SW BOR
}

