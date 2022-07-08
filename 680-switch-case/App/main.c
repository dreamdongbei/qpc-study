#include "bsp.h"
#include "button.h"
#include "sm_button.h"

sm_button_t sm;

int main(void)
{
    bsp_init();
    button_init();
    
    sm_button_init(&sm, ButtonId_UserKey);
    
    while (1)
    {
        sm_button_poll(&sm);
    }
}
