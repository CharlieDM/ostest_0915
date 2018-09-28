#include "bsp.h"
#include "data.h"
#include "ostest.h"

eSysState state = WAIT_START;

int main(void)
{	
    /* bsp init */
    bsp_init();
    
    /* show */
    show_init();
    
    while(1)
    {
        switch(state)
        {
            case WAIT_START:   
				/* refresh lcd */
				show_main();
				
                /* check start sign */
                if(wait_start_sign())
                {
                    state = ON_TEST;
                }
                break;
            
            case ON_TEST:                
                /* start test */                
                start_test();
            
                /* goto wait start */
                state = ON_TEST;
                break;
            
            default: break;
        }        
    }
}

