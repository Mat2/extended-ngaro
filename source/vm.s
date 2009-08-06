	.file	"vm.c"
	.text
.globl init_vm
	.type	init_vm, @function
init_vm:
	movl	4(%esp), %eax
	movl	$0, 8(%eax)
	movl	$0, (%eax)
	movl	$0, 4(%eax)
	movl	$1, %edx
.L2:
	movl	$0, 8(%eax,%edx,4)
	incl	%edx
	cmpl	$101, %edx
	jne	.L2
	movl	$0, %edx
.L4:
	movl	$0, 412(%eax,%edx,4)
	incl	%edx
	cmpl	$1024, %edx
	jne	.L4
	movl	$0, %edx
.L6:
	movl	$0, 8604(%eax,%edx,4)
	incl	%edx
	cmpl	$5000000, %edx
	jne	.L6
	movl	$0, %edx
.L8:
	movl	$0, 4508(%eax,%edx,4)
	incl	%edx
	cmpl	$1024, %edx
	jne	.L8
	ret
	.size	init_vm, .-init_vm
.globl vm_process
	.type	vm_process, @function
vm_process:
	subl	$44, %esp
	movl	%ebx, 28(%esp)
	movl	%esi, 32(%esp)
	movl	%edi, 36(%esp)
	movl	%ebp, 40(%esp)
	movl	48(%esp), %ebx
	movl	8(%ebx), %eax
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L52(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L52:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L210:
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L53(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L53:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L209:
	incl	(%ebx)
	incl	8(%ebx)
	movl	(%ebx), %eax
	movl	%esi, 12(%ebx,%eax,4)
	movl	8(%ebx), %eax
	movl	8604(%ebx,%eax,4), %esi
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L54(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L54:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L208:
	movl	(%ebx), %eax
	incl	%eax
	movl	%eax, (%ebx)
	movl	%esi, 12(%ebx,%eax,4)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L55(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L55:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L207:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %esi
	decl	%eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L56(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L56:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L206:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	movl	%esi, 12(%ebx,%eax,4)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	movl	%edx, %esi
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L86(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L86:
	.long	.L57
	.long	.L58
	.long	.L59
	.long	.L207
	.long	.L206
	.long	.L60
	.long	.L61
	.long	.L62
	.long	.L63
	.long	.L64
	.long	.L65
	.long	.L66
	.long	.L67
	.long	.L68
	.long	.L69
	.long	.L70
	.long	.L71
	.long	.L72
	.long	.L73
	.long	.L74
	.long	.L75
	.long	.L76
	.long	.L77
	.long	.L78
	.long	.L79
	.long	.L80
	.long	.L81
	.long	.L82
	.long	.L83
	.long	.L84
	.long	.L85
	.text
.L84:
	movl	%edx, %esi
	jmp	.L181
.L83:
	movl	%edx, %esi
	jmp	.L182
.L82:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L183
.L81:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L184
.L79:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L186
.L78:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L187
.L77:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L188
.L76:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L189
.L75:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L190
.L74:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L191
.L73:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L192
.L72:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L193
.L71:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L194
.L70:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L195
.L69:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L196
.L68:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L197
.L67:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L198
.L66:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L199
.L65:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L200
.L64:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L201
.L63:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L202
.L62:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L203
.L61:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L204
.L85:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L243
.L59:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L208
.L58:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L209
.L57:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L210
.L60:
	movl	%edx, %esi
.L205:
	movl	4(%ebx), %eax
	incl	%eax
	movl	%eax, 4(%ebx)
	movl	%esi, 412(%ebx,%eax,4)
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %esi
	decl	%eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L87(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L87:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L204:
	movl	(%ebx), %eax
	incl	%eax
	movl	%eax, (%ebx)
	movl	%esi, 12(%ebx,%eax,4)
	movl	4(%ebx), %eax
	movl	412(%ebx,%eax,4), %esi
	decl	%eax
	movl	%eax, 4(%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L88(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L88:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L203:
	incl	8(%ebx)
	movl	4(%ebx), %edx
	incl	%edx
	movl	%edx, 4(%ebx)
	movl	8(%ebx), %eax
	movl	%eax, 412(%ebx,%edx,4)
	movl	8604(%ebx,%eax,4), %eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L89(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L89:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L202:
	movl	8(%ebx), %eax
	incl	%eax
	movl	8604(%ebx,%eax,4), %eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L90(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L90:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L201:
	movl	4(%ebx), %eax
	movl	412(%ebx,%eax,4), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	decl	4(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L91(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L91:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L200:
	movl	8(%ebx), %edx
	incl	%edx
	movl	%edx, 8(%ebx)
	movl	(%ebx), %eax
	cmpl	12(%ebx,%eax,4), %esi
	jge	.L92
	movl	8604(%ebx,%edx,4), %eax
	movl	%eax, 8(%ebx)
	jmp	.L94
.L92:
	leal	1(%edx), %eax
	movl	%eax, 8(%ebx)
.L94:
	movl	(%ebx), %eax
	movl	8(%ebx,%eax,4), %esi
	subl	$2, %eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L95(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L95:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L199:
	movl	8(%ebx), %edx
	incl	%edx
	movl	%edx, 8(%ebx)
	movl	(%ebx), %eax
	cmpl	12(%ebx,%eax,4), %esi
	jle	.L96
	movl	8604(%ebx,%edx,4), %eax
	movl	%eax, 8(%ebx)
	jmp	.L98
.L96:
	leal	1(%edx), %eax
	movl	%eax, 8(%ebx)
.L98:
	movl	(%ebx), %eax
	movl	8(%ebx,%eax,4), %esi
	subl	$2, %eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L99(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L99:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L198:
	movl	8(%ebx), %edx
	incl	%edx
	movl	%edx, 8(%ebx)
	movl	(%ebx), %eax
	cmpl	12(%ebx,%eax,4), %esi
	je	.L100
	movl	8604(%ebx,%edx,4), %eax
	movl	%eax, 8(%ebx)
	jmp	.L102
.L100:
	leal	1(%edx), %eax
	movl	%eax, 8(%ebx)
.L102:
	movl	(%ebx), %eax
	movl	8(%ebx,%eax,4), %esi
	subl	$2, %eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L103(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L103:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L197:
	movl	8(%ebx), %edx
	incl	%edx
	movl	%edx, 8(%ebx)
	movl	(%ebx), %eax
	cmpl	12(%ebx,%eax,4), %esi
	jne	.L104
	movl	8604(%ebx,%edx,4), %eax
	movl	%eax, 8(%ebx)
	jmp	.L106
.L104:
	leal	1(%edx), %eax
	movl	%eax, 8(%ebx)
.L106:
	movl	(%ebx), %eax
	movl	8(%ebx,%eax,4), %esi
	subl	$2, %eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L107(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L107:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L196:
	movl	8604(%ebx,%esi,4), %esi
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L108(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L108:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L195:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	movl	%edx, 8604(%ebx,%esi,4)
	movl	8(%ebx,%eax,4), %esi
	subl	$2, %eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L109(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L109:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L194:
	movl	(%ebx), %eax
	addl	%esi, 12(%ebx,%eax,4)
	movl	12(%ebx,%eax,4), %esi
	decl	%eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L110(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L110:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L193:
	movl	(%ebx), %eax
	subl	%esi, 12(%ebx,%eax,4)
	movl	12(%ebx,%eax,4), %esi
	decl	%eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L111(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L111:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L192:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	imull	%esi, %edx
	movl	%edx, 12(%ebx,%eax,4)
	movl	%edx, %esi
	decl	%eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L112(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L112:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L191:
	movl	%esi, 20(%esp)
	movl	(%ebx), %ecx
	movl	12(%ebx,%ecx,4), %ebp
	movl	%ebp, %eax
	cltd
	idivl	%esi
	movl	%eax, %esi
	movl	%ebp, %eax
	cltd
	idivl	20(%esp)
	movl	%edx, 12(%ebx,%ecx,4)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L113(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L113:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L190:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	decl	%eax
	movl	%eax, (%ebx)
	andl	%edx, %esi
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L114(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L114:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L189:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	decl	%eax
	movl	%eax, (%ebx)
	orl	%edx, %esi
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L115(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L115:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L188:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	decl	%eax
	movl	%eax, (%ebx)
	xorl	%edx, %esi
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L116(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L116:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L187:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	decl	%eax
	movl	%eax, (%ebx)
	movl	%esi, %ecx
	sall	%cl, %edx
	movl	%edx, %esi
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L117(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L117:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L186:
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	decl	%eax
	movl	%eax, (%ebx)
	movl	%esi, %ecx
	sarl	%cl, %edx
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	movl	%edx, %esi
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L147(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L147:
	.long	.L118
	.long	.L119
	.long	.L120
	.long	.L207
	.long	.L121
	.long	.L122
	.long	.L123
	.long	.L124
	.long	.L125
	.long	.L126
	.long	.L127
	.long	.L128
	.long	.L129
	.long	.L130
	.long	.L131
	.long	.L132
	.long	.L133
	.long	.L134
	.long	.L135
	.long	.L136
	.long	.L137
	.long	.L138
	.long	.L139
	.long	.L140
	.long	.L186
	.long	.L141
	.long	.L142
	.long	.L143
	.long	.L144
	.long	.L145
	.long	.L146
	.text
.L145:
	movl	%edx, %esi
	jmp	.L181
.L144:
	movl	%edx, %esi
	jmp	.L182
.L143:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L183
.L142:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L184
.L141:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L185
.L140:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L187
.L139:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L188
.L138:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L189
.L137:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L190
.L136:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L191
.L135:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L192
.L134:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L193
.L133:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L194
.L132:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L195
.L131:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L196
.L130:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L197
.L129:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L198
.L128:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L199
.L127:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L200
.L126:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L201
.L125:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L202
.L124:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L203
.L123:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L204
.L122:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L205
.L121:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L206
.L146:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L243
.L120:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L208
.L119:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L209
.L118:
	movl	%edx, %esi
	.p2align 4,,5
	jmp	.L210
.L80:
	movl	%edx, %esi
.L185:
	testl	%esi, %esi
	.p2align 4,,3
	jne	.L148
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %esi
	decl	%eax
	movl	%eax, (%ebx)
	movl	4(%ebx), %eax
	movl	412(%ebx,%eax,4), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	decl	4(%ebx)
	jmp	.L150
.L148:
	incl	8(%ebx)
.L150:
	movl	8(%ebx), %eax
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L151(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L151:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L184:
	incl	%esi
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L152(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L152:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L183:
	decl	%esi
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L153(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L153:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L182:
	movl	%esi, %eax
	movl	4508(%ebx,%esi,4), %esi
	movl	$0, 4508(%ebx,%eax,4)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L154(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L154:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L181:
	movl	$0, 4508(%ebx)
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %edx
	movl	%edx, 4508(%ebx,%esi,4)
	movl	8(%ebx,%eax,4), %esi
	subl	$2, %eax
	movl	%eax, (%ebx)
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L155(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L155:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L243:
	movl	4508(%ebx), %eax
	cmpl	$1, %eax
	jne	.L156
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L158(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L158:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L156:
	testl	%eax, %eax
	jne	.L159
	cmpl	$1, 4512(%ebx)
	jne	.L159
	call	dev_getch
	movl	%eax, 4512(%ebx)
	movl	$1, 4508(%ebx)
.L159:
	cmpl	$1, 4516(%ebx)
	jne	.L162
	movl	%esi, (%esp)
	call	dev_putch
	movl	(%ebx), %eax
	movl	12(%ebx,%eax,4), %esi
	decl	%eax
	movl	%eax, (%ebx)
	movl	$0, 4516(%ebx)
	movl	$1, 4508(%ebx)
.L162:
	cmpl	$1, 4524(%ebx)
	jne	.L164
	leal	20008608(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	vm_save_image
	movl	$0, 4524(%ebx)
	movl	$1, 4508(%ebx)
.L164:
	cmpl	$-1, 4528(%ebx)
	jne	.L166
	movl	$5000000, 4528(%ebx)
	movl	$1, 4508(%ebx)
.L166:
	movl	4528(%ebx), %edx
	leal	3(%edx), %eax
	cmpl	$1, %eax
	jbe	.L168
	cmpl	$-4, %edx
	jne	.L170
.L168:
	movl	$0, 4528(%ebx)
	movl	$1, 4508(%ebx)
.L170:
	cmpl	$-5, 4528(%ebx)
	jne	.L171
	movl	(%ebx), %eax
	movl	%eax, 4528(%ebx)
	movl	$1, 4508(%ebx)
.L171:
	cmpl	$-6, 4528(%ebx)
	jne	.L173
	movl	4(%ebx), %eax
	movl	%eax, 4528(%ebx)
	movl	$1, 4508(%ebx)
.L173:
	movl	8(%ebx), %eax
	incl	%eax
	movl	%eax, 8(%ebx)
	cmpl	$30, 8604(%ebx,%eax,4)
	ja	.L20
	movl	8604(%ebx,%eax,4), %eax
	jmp	*.L175(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L175:
	.long	.L210
	.long	.L209
	.long	.L208
	.long	.L207
	.long	.L206
	.long	.L205
	.long	.L204
	.long	.L203
	.long	.L202
	.long	.L201
	.long	.L200
	.long	.L199
	.long	.L198
	.long	.L197
	.long	.L196
	.long	.L195
	.long	.L194
	.long	.L193
	.long	.L192
	.long	.L191
	.long	.L190
	.long	.L189
	.long	.L188
	.long	.L187
	.long	.L186
	.long	.L185
	.long	.L184
	.long	.L183
	.long	.L182
	.long	.L181
	.long	.L243
	.text
.L20:
	movl	$5000000, 8(%ebx)
	movl	28(%esp), %ebx
	movl	32(%esp), %esi
	movl	36(%esp), %edi
	movl	40(%esp), %ebp
	addl	$44, %esp
	ret
	.size	vm_process, .-vm_process
	.ident	"GCC: (GNU) 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)"
	.section	.note.GNU-stack,"",@progbits
