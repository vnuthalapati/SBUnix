.text
.global idt_ins
idt_ins:
        lidt (%rdi)
        retq
