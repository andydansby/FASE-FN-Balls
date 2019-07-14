DEFINE  port    $5c01
DEFINE  screen  $5c00
;5b5c system variable update peek 23388
; port 7ffd 32765



;LINE 212
      IF  machine=1             ; if not 48k sync with interrupt 
        ld      hl, do1
        ei
do1     jp      (hl)
        ld      bc, $7ffd
      IF player
        ld      a, $11
        out     (c), a
      ELSE
        ld      a, (port&$ffff) ; toggle port value between 00 and 80 every frame
        xor     $80
        ld      (port&$ffff), a
        ld      a, $18          ; also toggle between bank 5 & 7 for the screen
        jr      z, do2          ; and 7 & 0 for the current paging at $c000
        dec     a               ; so we always show a screen and modify the other
do2     out     (c), a
      ENDIF
---------------------------------
;LINE 263
      IF  machine=1
        ld      bc, $7ffd
        ld      a, (port)
        rla
        ld      e, $10
        jr      c, desc2
        ld      e, $1f
desc2   out     (c), e
        ld      a, do4-2-do3
        ld      (do3+1), a
        ld      a, e
        xor     $07
        out     (c), a
        inc     b
      ELSE
        ld      b, $80          ; marker bit
      ENDIF
---------------------------------
;LINE 718
      IF  machine=1
        ld      h, c            ; in this code we store the read
        ld      bc, $7ffd       ; values to use in the next frame
        ld      a, (port)
        rla
        ld      e, $10
        jr      c, uppa4
        ld      e, $1f
uppa4   out     (c), e
        ld      (update_partial+1), a
        ld      a, l
        ld      (uppa1+1), a
        ld      a, h
        ld      (uppa2+1), a
        ld      a, e
        xor     $07
        out     (c), a
        ld      c, h
uppa5   ld      a, l
      ENDIF

---------------------------------
;line 1427
    IF  machine=1
        ld      (delete_sprites+1), bc
        ld      hl, (drwout)
        ld      a, h
        inc     a
        ld      sp, screen-1
        jr      z, drawx
        call    $162c
        ld      a, ($5bff)
        xor     $ff
        jr      nz, drawx
        dec     a
        ld      (drwout+1), a
drawx   ld      ($5bff), a
        ld      bc, $7ffd
        ld      a, (port)
        rla
        ld      a, $10
        jr      c, drawy
        ld      a, $18
drawy   out     (c), a
drawz   ld      sp, 0
        ret
    ELSE
drawz   ld      sp, 0
        ld      (delete_sprites+1), bc
        ld      hl, (drwout)
        ld      a, h
        inc     a
        ret     z
        ld      a, $ff
        ld      (drwout+1), a
        jp      (hl)
    ENDIF
	
	
---------------------------------
;LINE 1938
    IF  machine=1
        ld      (do3+1), a
        ld      (port), a

        ld      sp, $fff4
        ld      l, $23
        ex      (sp), hl
        ld      (exit+1&$ffff), hl
        inc     sp
        ld      hl, $c3c9
        ex      (sp), hl
        ld      a, h
        ld      (exit1+1&$ffff), a

        ld      sp, $5c06
        ld      hl, ini2&$ffff
        ld      de, $5b00
      IF atrbar=0
        ld      c, ini5-ini2
      ELSE
        ld      bc, ini5-ini2
      ENDIF
        ldir
        ld      hl, $db00
        call    $5b00
        ld      a, $ff
        ld      (screen), a
        ld      (selbeg), a
        ld      (drwout+1), a
;        dec     a
;        ld      i, a
;        im      2
ini8    ld      sp, 0
        ret
ini2    ld      c, $ff+ini2-ini5&$ff
        ldir
        ld      a, $17
        call    $5b00+ini4-ini2
        ld      c, $ff+ini2-ini5&$ff
        ex      de, hl
        dec     e
        dec     l
        lddr
        inc     e
        inc     l
        ex      de, hl
        ld      c, $ff+ini2-ini5&$ff
        add     hl, bc
        ld      a, $10
        call    $5b00+ini4-ini2
        jr      nc, ini2
        call    $5b00+ini3-ini2
        ld      hl, $4000
        ld      de, $c000
        ld      bc, $1b00
        ldir
ini3    xor     $07
ini4    push    bc
        ld      bc, $7ffd
        out     (c), a
        pop     bc
        ret
ini5
exit    ld      hl, 0
        ld      ($fff4), hl
exit1   ld      a, 0
        ld      ($fff6), a

        ld      a, $10
        jr      ini4
    ENDIF