	.text

/* Switch from current_thread to next_thread. Make next_thread
 * the current_thread, and set next_thread to 0.
 * Use eax as a temporary register; it is caller saved.
 */
	.globl thread_switch
thread_switch:
	pushal
	movl current_thread, %eax
	movl %esp, (%eax)
	movl next_thread, %eax
	movl (%eax), %esp
	movl %eax, current_thread
	movl $0, next_thread
	popal	
	/* YOUR CODE HERE */
	ret				/* pop return address from stack */
