.macro  PUSHALL
        pushq %rax
        pushq %rbx
        pushq %rcx
        pushq %rdx
        pushq %rbp
        pushq %rdi
        pushq %rsi
        pushq %r8
        pushq %r9
        pushq %r10
        pushq %r11
        pushq %r12
        pushq %r13
        pushq %r14
        pushq %r15
	pushq %rsp
.endm

.macro  POPALL
	popq %rsp
        popq %r15
        popq %r14
        popq %r13
        popq %r12
        popq %r11
        popq %r10
        popq %r9
        popq %r8
        popq %rsi
        popq %rdi
        popq %rbp
        popq %rdx
        popq %rcx
        popq %rbx
        popq %rax
.endm
.data
.global final_rsp
final_rsp:
.word
.text
.global isr0
        isr0:
        PUSHALL
	movq %rsp, %rdi
        call common_handler
        POPALL
        iretq

.global isr1
isr1:
PUSHALL
call common_handler
POPALL
iretq


.global isr2
isr2:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr3
isr3:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr4
isr4:
cli
PUSHALL
call common_handler
POPALL
sti
iretq

.global isr5
isr5:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr6
isr6:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr7
isr7:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr8
isr8:
cli
PUSHALL
call common_handler
POPALL
sti
iretq

.global isr9
isr9:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr10
isr10:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr11
isr11:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr12
isr12:
cli
PUSHALL
call common_handler
POPALL
sti
iretq
.global isr13
isr13:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr14
isr14:
PUSHALL
movw $0x10,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
movq %rsp,%rdi;
call fault_handler
movw $0x23,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
POPALL
addq $0x08,%rsp;
iretq

.global isr15
isr15:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr16
isr16:
cli
PUSHALL
call common_handler
POPALL
sti
iretq
.global isr17
isr17:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr18
isr18:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr19
isr19:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr20
isr20:
cli
PUSHALL
call common_handler
POPALL
sti
iretq
.global isr21
isr21:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr22
isr22:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr23
isr23:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr24
isr24:
cli
PUSHALL
call common_handler
POPALL
sti
iretq
.global isr25
isr25:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr26
isr26:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr27
isr27:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr28
isr28:
cli
PUSHALL
call common_handler
POPALL
sti
iretq

.global isr29
isr29:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr30
isr30:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr31
isr31:
cli
PUSHALL
call common_handler
POPALL
sti
iretq


.global isr32
isr32:
pushq $0x0;
PUSHALL
movw $0x10,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
movq %rsp, %rdi
call timer_handler
POPALL
addq $0x8,%rsp;
iretq

.global isr33
isr33:
pushq $0x0;
PUSHALL
movw $0x10,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
movq %rsp, %rdi
call kbd_handler
movw $0x23,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
POPALL
addq $0x8,%rsp
iretq


.global isr128
isr128:
pushq $0x0;
PUSHALL
movw $0x10,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
movq %rsp, %rdi
call trap_handler
movw $0x23,%ax;
movw %ax,%ds;
movw %ax,%es;
movw %ax,%fs;
movw %ax,%gs;
POPALL
addq $0x8,%rsp
iretq

