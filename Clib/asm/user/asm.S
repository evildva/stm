	preserve8
	area asmcode,code,readonly
	export addnum
	export runapp
	import multiple
	import ma
	import mb
		
addnum
	push {r0,r1,LR}
	ldr r0,=ma
	ldr r1,=mb
	ldr r0,[r0]
	ldr r1,[r1]
	bl multiple
	pop {r1,r2}
	add r0,r0,r1
	add r0,r0,r2
	pop {lr}    ;or pop {pc}
	bx lr
	
runapp
	
	
	end