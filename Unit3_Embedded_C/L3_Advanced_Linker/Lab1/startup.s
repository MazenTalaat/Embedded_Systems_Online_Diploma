@@ Mazen Talaat U3 L2 10-Nov-2021
.global reset
reset:
        ldr sp, =stack_top
        bl main
stop:   b stop
