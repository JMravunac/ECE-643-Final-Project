#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "hps_0.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

int main() {

	void *virtual_base;
	int fd;
	int loop_count;
	int led_direction;
	int led_mask;
	void *h2p_lw_led_addr;
	void *h2p_lw_s_addr;
	void *h2p_lw_p_addr;
	void *p2h_lw_a_addr;
	void *p2h_lw_b_addr;
	
	float a, b, p, s;
	float *p_fpga;
	float *s_fpga;

	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}
	
	h2p_lw_led_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_LED_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	h2p_lw_s_addr=virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + S_PIO_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	h2p_lw_p_addr=virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + P_PIO_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	p2h_lw_a_addr=virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + A_PIO_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	p2h_lw_b_addr=virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + B_PIO_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	
	int select = 0;	
	int loop = 1;
	int select = 0;
	int select_value = 0;
	
	int dist_en = 0;
	int dist_gain = 0;
	int dist_level = 0;
	
	int loop_en = 0;
	
	int chorus_en = 0;
	int chorus_level = 0;
	int chorus_depth = 0;
	int chorus_rate = 0;
	
	int eq_en = 0;
	int eq_low = 0;
	int eq_mid = 0;
	int eq_high = 0;
	
	int flanger_en = 0;
	int flanger_speed = 0;
	int flanger_depth = 0;
	int flanger_delayTime = 0;
	
	while(1)
	{
		
		printf("Select Pedal to Adjust:/n");
		printf("1: Distortion/n");
		printf("2: Loop/n");
		printf("3: Chorus/n");
		printf("4: 3 Band EQ/n");
		printf("5: Flanger/n");
		
		scanf("%d", &select);
		
		loop = 1;
		
		switch(select)
		{
			if(select == 1)
			{
				while(loop)
				{
					printf("Distortion/n");
					printf("Enter selection followed by desired new value/n");
					printf("1: Enabled - %d/n", dist_en);
					printf("2: Gain - Current Value = %d/n",dist_gain);
					printf("3: Level - Current Value = %d/n",dist_level);					
					printf("4: Exit/n");
					scanf("%d%d", &select, %select_value );	
					
					if(select == 1)
					{						
						dist_en = select_value;
					}
					else if(select == 2)
					{
						dist_gain = select_value;
					}
					else if(select == 3)
					{
						dist_level = select_value;
					}
					else if(select == 4)
					{
						loop = 0;
					}
					
				}
					
			}
			else if(select==2)
			{
				while(loop)
				{
					printf("Loop/n");
					printf("Enter selection followed by desired new value/n");
					printf("1: Enabled - %d/n", loop_en);				
					printf("2: Exit/n");
					scanf("%d%d", &select, %select_value );	
					
					if(select == 1)
					{						
						loop_en = select_value;
					}
					else if(select == 2)
					{
						loop = 0;
					}
					
				}
			}
			else if(select==3)
			{
				while(loop)
				{
					printf("Chorus Effect/n");
					printf("Enter selection followed by desired new value/n");
					printf("1: Enabled - %d/n", chorus_en);
					printf("2: Level - Current Value = %d/n",chorus_level);
					printf("3: Depth - Current Value = %d/n",chorus_depth);
					printf("4: Rate - Current Value = %d/n",chorus_rate);
					printf("5: Exit/n");
					scanf("%d%d", &select, %select_value );	
					
					if(select == 1)
					{						
						chorus_en = select_value;
					}
					else if(select == 2)
					{
						chorus_level = select_value;
					}
					else if(select == 3)
					{
						chorus_depth = select_value;
					}
					else if(select == 4)
					{
						chorus_rate = select_value;
					}
					else if(select == 5)
					{
						loop = 0;
					}
					
				}
			}
			else if(select==4)
			{
				while(loop)
				{
					printf("3 Band EQ/n");
					printf("Enter selection followed by desired new value/n");
					printf("1: Enabled - %d/n", eq_en);
					printf("2: Low - Current Value = %d/n",eq_low);
					printf("3: Mid - Current Value = %d/n",eq_mid);
					printf("4: High - Current Value = %d/n",eq_high);
					printf("5: Exit/n");
					scanf("%d%d", &select, %select_value );	
					
					if(select == 1)
					{						
						eq_en = select_value;
					}
					else if(select == 2)
					{
						eq_low = select_value;
					}
					else if(select == 3)
					{
						eq_mid = select_value;
					}
					else if(select == 4)
					{
						eq_high = select_value;
					}
					else if(select == 5)
					{
						loop = 0;
					}
					
				}
			}
			else if(select==5)
			{
				while(loop)
				{
					printf("Flanger Effect/n");
					printf("Enter selection followed by desired new value/n");
					printf("1: Enabled - %d/n", flanger_en);
					printf("2: Speed - Current Value = %d/n",flanger_speed);
					printf("3: Depth - Current Value = %d/n",flanger_depth);
					printf("4: Delay Time - Current Value = %d/n",flanger_delayTime);
					printf("5: Exit/n");
					scanf("%d%d", &select, %select_value );	
					
					if(select == 1)
					{						
						flanger_en = select_value;
					}
					else if(select == 2)
					{
						flanger_speed = select_value;
					}
					else if(select == 3)
					{
						flanger_depth = select_value;
					}
					else if(select == 4)
					{
						flanger_delayTime = select_value;
					}
					else if(select == 5)
					{
						loop = 0;
					}
					
				}
			}
		}
	}


	

	// clean up our memory mapping and exit
	
	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );
}
