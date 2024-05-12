someVar = $10 ; This is a variable assignment
anotherVar = %0101 ; This is another assignment

jsr init
jsr runTests
jsr done

init:
  sei         ; Disable IRQs
  cld         ; Disable decimal mode
  ldx #$FF    ; Initialize Stack
  txs         ; Set the stack pointer to $FF
  lda someVar ; This should reference the assigned definition
  rts         ; return

runTests:
  jsr testADC
  rts


;; ADC Tests ;;
;; ----------;;
;; This tests whether ADC works as expected as well as checking whether 
;; the following addressing modes work as intended:
;;    - Immediate
;;    - ZeroPage
;;    - ZeroPageX
;;    - Absolute
;;    - AbsoluteX
;;
;;
;; Testing without Carry Flag, tests Immediate and ZeroPage addressing
;; Flag explicitly cleared before each operation
testADC:
  clc          ; Clear the Carry Flag
  lda #$02     ; Load $02 into the accumulator
  adc #$F0     ; Add $F0
  cmp #$F2     ; Check if the result is indeed $F2
  sta $00      ; Store result at $00

  clc          ; Clear the Carry flag again
  lda #$20     ; Load $20 into accumulator
  sta $FF      ; Store $20 at 0x00FF
  adc $FF      ; Load $20 stored at 0x00FF into A
  cmp #$40     ; Compare accumulaotr against $40
  sta $01      ; Store result at 0x01 if it is wrong

  ;; Testing WITH Carry Flag, also tests Absolute addressing and ZeroPageX addressing
  sec          ; Set the Carry Flag
  ldx #$60     ; Load $60 into X
  lda #$10     ; Load $10 into A
  sta $20      ; Store A at 0x0020
  lda $C0,X    ; Loads address $C0+$60=$120, however this should wrap around to $20. Stored value if $10
  cmp #$10     ; Compare A against 10, if not 10, then reading has went wrong
  sta $02      ; Store result 
  lda #$10     ; Load $10 into A
  sta $0211    ; Store $10 at 0x0111
  adc $0211    ; Add the value $10 stored at 0x0211 to A (result should be $10+$10+$01=$21 due to carry)
  cmp #$21     ; Check if result correct
  sta $03      ; Store result
  php          ; Push the processor status to the stack
  lda #$01     ; Load the bit pattern 0b00000001 (Carry flag) into the accumulator
  bit $01FE    ; Check the value pushed to the stack if the carry flag has been set (It should be clear)
  sta $04      ; Otherwise store the result


  rts          ; return

done:
  brk
