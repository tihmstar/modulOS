ENTRY(_entrypoint)

SECTIONS
{
    . = 0x00000000;

    file_start = .;

    .text.boot : {
        *(.text.boot)
    }

    . = ALIGN(8);

    .text.target_entry : {
        *(.text.boot)
    }

    . = ALIGN(8);

    .text : {
        *(.text)
    }

    . = ALIGN(8);

    .data : {
        *(.data)
    }

    . = ALIGN(8);

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }
    . = ALIGN(8);
    
    .got : {
        *(.got)
    }

    . = ALIGN(8);

    .rela.plt : {
        *(.rela.plt)
    }

    . = ALIGN(0x1000);
    start_rw_section = .;


    .bss : {
        *(.bss)
    }

    /*
      Static variables should go here
    */

    . = ALIGN(0x1000);
    early_stack_start = .;
    . += 0x1000;
    early_stack_end = .;
    early_stack_end_offset = early_stack_end - file_start;

    /*
      Below this line is empty sections!
    */

    . = ALIGN(0x4000);
    .pagetables : {
        *(.pagetables)
    }
    
    . = ALIGN(8);

    .data_at_the_end : {
        *(.end_data)
    }

    appended_data_start = .;

    . = ALIGN(0x1000);
    .boot.stack : {
      *(.boot.stack)
    }

    end = .;
    file_size = end - file_start;

    /DISCARD/ : {
        *(.ARM.exidx)
    }
}
