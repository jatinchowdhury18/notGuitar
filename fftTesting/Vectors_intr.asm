*Vectors_intr.asm Vector file for interrupt INT11
   .global _vectors			;global symbols
   .global _c_int00
   .global _vector1
   .global _vector2
   .global _vector3
   .global _vector4
   .global _vector5
   .global _vector6
   .global _vector7
   .global _vector8
   .global _vector9	  
   .global _vector10 
   .global _c_int11  			;for INT11
   .global _vector12  
   .global _vector13   
   .global _vector14
   .global _vector15

   .ref _c_int00				;entry address

VEC_ENTRY .macro addr			;macro for ISR
    STW   B0,*--B15
    MVKL  addr,B0
    MVKH  addr,B0
    B     B0
    LDW   *B15++,B0
    NOP   2
    NOP   
    NOP   
   .endm

_vec_dummy:
  B    B3
  NOP  5

 .sect ".vecs"				;aligned IST section
 .align 1024
_vectors:
_vector0:   VEC_ENTRY _c_int00   	;RESET
_vector1:   VEC_ENTRY _vec_dummy  	;NMI
_vector2:   VEC_ENTRY _vec_dummy  	;RSVD
_vector3:   VEC_ENTRY _vec_dummy
_vector4:   VEC_ENTRY _vec_dummy
_vector5:   VEC_ENTRY _vec_dummy
_vector6:   VEC_ENTRY _vec_dummy
_vector7:   VEC_ENTRY _vec_dummy
_vector8:   VEC_ENTRY _vec_dummy
_vector9:   VEC_ENTRY _vec_dummy
_vector10:  VEC_ENTRY _vec_dummy
_vector11:  VEC_ENTRY _c_int11    	;ISR address
_vector12:  VEC_ENTRY _vec_dummy
_vector13:  VEC_ENTRY _vec_dummy
_vector14:  VEC_ENTRY _vec_dummy
_vector15:  VEC_ENTRY _vec_dummy
