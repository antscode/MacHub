#include "Dialogs.r"

resource 'DLOG' (128, purgeable) {
	{ 50, 100, 368, 600 },
	movableDBoxProc,
	visible,
	goAway,
	0,
	128,
	"Preferences",
	centerMainScreen
};

/* Require to enable colour in the dialog */
data 'dctb' (128, purgeable) {
   $"0000 0000 0000 FFFF"  /*use default colors*/
};

resource 'DITL' (128, purgeable) {
	{
		{ 10, 10, 30, 100 },
		StaticText { enabled, "Accounts" };

		{ 35, 10, 200+40, 200+10 },
		UserItem { enabled };

		{ 35, 220, 200+40, 200+220 },
		UserItem { enabled };

		{ 250, 10, 270, 110 },
		Button { enabled, "Add Account" };

		{ 250, 130, 270, 211 },
		Button { enabled, "Remove" };

		{ 285, 208-70, 305, 207 },
		Button { enabled, "Done" };
	}
};

/* The 10-byte code resource stub trick.
 *
 * The bytes in this resource are 68K machine code for
 *     move.l L1(pc), -(sp)    | 2F3A 0004
 *     rts                     | 4E75
 * L1: dc.l 0x00000000         | 0000 0000
 *
 * The application loads this resource and replaces the final four bytes
 * with the address of the WDEF function in wdef.c, which is compiled as part
 * of the application.
 */
data 'LDEF' (128) {
    $"2F3A 0004 4E75 0000 0000"
}; 

data 'PICT' (128, "facebook") {
	$"0724 0000 0000 0020 0020 0011 02FF 0C00"            /* .$..... . ...... */
	$"FFFE 0000 0048 0000 0048 0000 0000 0000"            /* .....H...H...... */
	$"0020 0020 0000 0000 00A1 01F2 0016 3842"            /* . . .....°....8B */
	$"494D 0000 0000 0000 0020 0020 4772 8970"            /* IM....... . Grâp */
	$"68AF 626A 0001 000A 0000 0000 0020 0020"            /* hØbj......... .  */
	$"009A 0000 00FF 8080 0000 0000 0020 0020"            /* .ö....ÄÄ..... .  */
	$"0000 0004 0000 0000 0048 0000 0048 0000"            /* .........H...H.. */
	$"0010 0020 0003 0008 0000 0000 0000 0000"            /* ... ............ */
	$"0000 0000 0000 0000 0020 0020 0000 0000"            /* ......... . .... */
	$"0020 0020 0040 1A02 D85D 44E7 4805 4455"            /* . . .@..ÿ]D.H.DU */
	$"C4DE 7661 E764 0461 6FCD E4AB E59F 01A7"            /* ƒ.va.d.aoÕ.´.ü.ß */
	$"D718 014E 39E5 3B03 393D 6957 E559 0457"            /* ◊..N9.;.9=iW.Y.W */
	$"5AA0 9C97 E798 0297 9C9A 0FE2 3B00 3EE2"            /* Z†úó.ò.óúö..;.>. */
	$"5902 5B9A 97E5 9801 979B 3200 47EF 3B0D"            /* Y.[öó.ò.óõ2.G.;¬ */
	$"3C3B 3127 2324 282B 393D 3B3B 4663 EF59"            /* <;1'#$(+9=;;Fc.Y */
	$"0D5A 5950 4845 4649 4C57 5B59 5962 9EED"            /* ¬ZYPHEFILW[YYbû. */
	$"980A 938E 8C8C 8E90 9799 9898 9E36 0047"            /* ò.ìéååéêóôòòû6.G */
	$"F03B 0E3F 2B1A 3751 5C59 5046 3B3A 3B3B"            /* .;.?+.7Q\YPF;:;; */
	$"4663 F059 0E5D 4C3D 566C 7572 6B63 5958"            /* Fc.Y.]L=VlurkcYX */
	$"5959 629E F098 089A 9087 96A4 A9A8 A39E"            /* YYbû.ò.öêáñ§©®£û */
	$"FD98 009E 3A00 47F1 3B0F 401F 309A E4FE"            /* .ò.û:.G.;.@.0ö.. */
	$"FFFF FDF5 5A25 3B3B 4663 F159 0F5D 4150"            /* ....Z%;;Fc.Y.]AP */
	$"AAE8 FEFF FFFE F774 4659 5962 9EF1 980E"            /* ™......tFYYbû.ò. */
	$"9B89 93CA F1FE FFFF FEFA A88C 9898 9E31"            /* õâì ......®åòòû1 */
	$"0047 F23B 033E 2040 E2FA FF05 6121 3B3B"            /* .G.;.> @....a!;; */
	$"4663 F259 035C 425E E6FA FF05 7A42 5959"            /* Fc.Y.\B^....zBYY */
	$"629E F298 039A 8A9B F0FA FF04 AC8A 9898"            /* bû.ò.öäõ....¨äòò */
	$"9E2E 0047 F23B 0233 26E4 F9FF 055E 233B"            /* û..G.;.3&....^#; */
	$"3B46 63F2 5902 5348 E8F9 FF05 7744 5959"            /* ;Fc.Y.SH....wDYY */
	$"629E F298 0294 8DF1 F9FF 04AA 8B98 989E"            /* bû.ò.îç....™ãòòû */
	$"2B00 47F2 3B01 1780 F8FF 0563 1F3B 3B46"            /* +.G.;..Ä...c.;;F */
	$"63F2 5901 3B94 F8FF 057C 4159 5962 9EF2"            /* c.Y.;î...|AYYbû. */
	$"9801 85BD F8FF 04AD 8998 989E 3D00 47F3"            /* ò.ÖΩ...≠âòòû=.G. */
	$"3B02 3A1B BCFD FF0A F79C 8088 8849 323B"            /* ;.:.º....úÄààI2; */
	$"3B46 63F3 5902 583E C6FD FF0A F9AB 949A"            /* ;Fc.Y.X>∆....´îö */
	$"9B65 5159 5962 9EF3 9802 9787 DCFD FF09"            /* õeQYYbû.ò.óá...∆ */
	$"FBCB BCC1 C19F 9398 989E 3D00 47F3 3B02"            /* .Àº¡¡üìòòû=.G.;. */
	$"3629 D3FD FF0A 8800 1619 1935 3F3B 3B46"            /* 6)”...à....5?;;F */
	$"63F3 5902 554A DAFD FF0A 9A20 3A3C 3C54"            /* c.Y.UJ....ö :<<T */
	$"5D59 5962 9EF3 9802 958F E8FD FF09 C175"            /* ]YYbû.ò.ïè...∆¡u */
	$"8586 8695 9A98 989E 3300 47F3 3B02 352C"            /* ÖÜÜïöòòû3.G.;.5, */
	$"D4FD FF02 5E1D 3CFB 3B01 4663 F359 0254"            /* ‘...^.<.;.Fc.Y.T */
	$"4CDB FDFF 0277 3F5A FB59 0162 9EF3 9802"            /* L....w?Z.Y.bû.ò. */
	$"9590 E9FD FF01 AB88 FA98 009E 3100 47F3"            /* ïê....´à.ò.û1.G. */
	$"3B02 352B D2FD FF01 641F FA3B 0146 63F3"            /* ;.5+“...d..;.Fc. */
	$"5902 544B D9FD FF01 7C42 FA59 0162 9EF3"            /* Y.TK....|B.Y.bû. */
	$"9802 9590 E8FD FF01 AE89 FA98 009E 4900"            /* ò.ïê....Æâ.ò.ûI. */
	$"47F7 3B06 3D39 2221 1A0F CCFD FF0A 5201"            /* G.;.=9"!..Ã...R. */
	$"2120 233B 3D3B 3B46 63F7 5906 5B58 4443"            /* ! #;=;;Fc.Y.[XDC */
	$"3D33 D4FD FF0A 6D29 4343 4559 5A59 5962"            /* =3‘...m)CCEYZYYb */
	$"9EF7 9806 9997 8B8A 8781 E5FD FF09 A479"            /* û.ò.ôóãäáÅ...∆§y */
	$"8A8A 8B98 9998 989E 4900 47F7 3B06 383E"            /* ääãòôòòûI.G.;.8> */
	$"6063 5D55 DBFD FF0A 854C 6263 623E 383B"            /* `c]U....ÖLbcb>8; */
	$"3B46 63F7 5906 565B 797B 766F E1FD FF0A"            /* ;Fc.Y.V[y{vo.... */
	$"9868 7A7B 7A5C 5659 5962 9EF7 9806 9699"            /* òhz{z\VYYbû.ò.ñô */
	$"ACAD AAA6 EDFD FF01 BFA1 FEAD 049A 9698"            /* ¨≠™¶....ø°.≠.öñò */
	$"989E 2E00 47F7 3B01 2A48 F4FF 06F3 3A2F"            /* òû..G.;.*H....:/ */
	$"3B3B 4663 F759 014A 65F4 FF06 F558 4F59"            /* ;;Fc.Y.Je....XOY */
	$"5962 9EF7 9801 8F9E F4FF 05F9 9892 9898"            /* Ybû.ò.èû....òíòò */
	$"9E31 0047 F73B 022A 47FD F5FF 06D8 2836"            /* û1.G.;.*G....ÿ(6 */
	$"3B3B 4663 F759 024A 64FE F5FF 06DE 4955"            /* ;;Fc.Y.Jd.....IU */
	$"5959 629E F798 0290 9EFD F5FF 05EA 8E95"            /* YYbû.ò.êû.....éï */
	$"9898 9E31 0047 F73B 022B 47F6 F5FF 01A9"            /* òòû1.G.;.+G....© */
	$"18FE 3B01 4663 F759 024B 64F8 F5FF 01B6"            /* ..;.Fc.Y.Kd....∂ */
	$"3BFE 5901 629E F798 0290 9EFA F5FF 01D2"            /* ;.Y.bû.ò.êû....“ */
	$"86FE 9800 9E2E 0047 F73B 0128 49F4 FF01"            /* Ü.ò.û..G.;.(I... */
	$"8E11 FE3B 0146 63F7 5901 4966 F4FF 019F"            /* é..;.Fc.Y.If...ü */
	$"36FE 5901 629E F798 018F 9FF4 FF01 C482"            /* 6.Y.bû.ò.èü...ƒÇ */
	$"FE98 009E 4900 47F7 3B06 3143 B1B7 B4B1"            /* .ò.ûI.G.;.1C±∑¥± */
	$"EFFD FF05 C7AC B7B7 5E28 FE3B 0146 63F7"            /* ....«¨∑∑^(.;.Fc. */
	$"5906 5060 BDC2 C0BD F1FD FF05 CFB9 C2C2"            /* Y.P`Ω¬¿Ω....œπ¬¬ */
	$"7649 FE59 0162 9EF7 9806 939C D6D9 D8D6"            /* vI.Y.bû.ò.ìú÷.ÿ÷ */
	$"F7FD FF05 E2D4 D9D9 AB8E FE98 009E 4900"            /* .....‘..´é.ò.ûI. */
	$"47F7 3B06 3D39 201F 180C CCFD FF05 5000"            /* G.;.=9 ...Ã...P. */
	$"1F1F 3140 FE3B 0146 63F7 5906 5B57 4241"            /* ..1@.;.Fc.Y.[WBA */
	$"3B32 D4FD FF05 6B26 4141 515D FE59 0162"            /* ;2‘...k&AAQ].Y.b */
	$"9EF7 9806 9997 8A89 8680 E5FD FF05 A378"            /* û.ò.ôóäâÜÄ....£x */
	$"8989 939A FE98 009E 3E00 47F5 3BFF 3902"            /* ââìö.ò.û>.G.;.9. */
	$"3329 D2FD FF04 641D 3939 3AFD 3B01 4663"            /* 3)“...d.99:.;.Fc */
	$"F559 FF57 0252 4AD9 FDFF 037D 4057 57FC"            /* .Y.W.RJ....}@WW. */
	$"5901 629E F598 FF97 0294 8FE8 FDFF 03AE"            /* Y.bû.ò.ó.îè....Æ */
	$"8897 97FC 9800 9E31 0047 F33B 0235 2BD2"            /* àóó.ò.û1.G.;.5+“ */
	$"FDFF 0166 1FFA 3B01 4663 F359 0254 4CD9"            /* ...f..;.Fc.Y.TL. */
	$"FDFF 017E 42FA 5901 629E F398 0295 90E8"            /* ...~B.Y.bû.ò.ïê. */
	$"FDFF 01AF 89FA 9800 9E31 0047 F33B 0235"            /* ...Øâ.ò.û1.G.;.5 */
	$"2BD2 FDFF 0166 1FFA 3B01 4663 F359 0254"            /* +“...f..;.Fc.Y.T */
	$"4CD9 FDFF 017E 42FA 5901 629E F398 0295"            /* L....~B.Y.bû.ò.ï */
	$"90E8 FDFF 01AF 89FA 9800 9E31 0047 F33B"            /* ê....Øâ.ò.û1.G.; */
	$"0235 2BD2 FDFF 0166 1FFA 3B01 4663 F359"            /* .5+“...f..;.Fc.Y */
	$"0254 4CD9 FDFF 017E 42FA 5901 629E F398"            /* .TL....~B.Y.bû.ò */
	$"0295 90E8 FDFF 01AF 89FA 9800 9E31 0047"            /* .ïê....Øâ.ò.û1.G */
	$"F33B 0235 2BD2 FDFF 0166 1FFA 3B01 4663"            /* .;.5+“...f..;.Fc */
	$"F359 0254 4CD9 FDFF 017E 42FA 5901 629E"            /* .Y.TL....~B.Y.bû */
	$"F398 0295 90E8 FDFF 01AF 89FA 9800 9E31"            /* .ò.ïê....Øâ.ò.û1 */
	$"0047 F33B 0235 2BD2 FDFF 0166 1FFA 3B01"            /* .G.;.5+“...f..;. */
	$"4663 F359 0254 4CD9 FDFF 017E 42FA 5901"            /* Fc.Y.TL....~B.Y. */
	$"629E F398 0295 90E8 FDFF 01AF 89FA 9800"            /* bû.ò.ïê....Øâ.ò. */
	$"9E31 0047 F33B 0235 2BD2 FDFF 0166 1FFA"            /* û1.G.;.5+“...f.. */
	$"3B01 4663 F359 0254 4CD9 FDFF 017E 42FA"            /* ;.Fc.Y.TL....~B. */
	$"5901 629E F398 0295 90E8 FDFF 01AF 89FA"            /* Y.bû.ò.ïê....Øâ. */
	$"9800 9E31 0047 F33B 0235 2BD2 FDFF 0166"            /* ò.û1.G.;.5+“...f */
	$"1FFA 3B01 4663 F359 0254 4CD9 FDFF 017E"            /* ..;.Fc.Y.TL....~ */
	$"42FA 5901 629E F398 0295 90E8 FDFF 01AF"            /* B.Y.bû.ò.ïê....Ø */
	$"89FA 9800 9E33 003D F33B 0235 2BD2 FDFF"            /* â.ò.û3.=.;.5+“.. */
	$"0166 1FFA 3B01 405B F359 0254 4CD9 FDFF"            /* .f..;.@[.Y.TL... */
	$"017E 42FA 5902 5D9C 97F4 9802 9590 E8FD"            /* .~B.Y.]úó.ò.ïê.. */
	$"FF01 AF89 FB98 0197 9C39 0142 39F4 3B02"            /* ..Øâ.ò.óú9.B9.;. */
	$"352B D2FD FF01 661F FB3B FF3A 015F 57F4"            /* 5+“...f..;.:._W. */
	$"5902 544C D9FD FF01 7E42 FB59 FF58 FF9C"            /* Y.TL....~B.Y.X.ú */
	$"0097 F598 0295 90E8 FDFF 01AF 89FC 9802"            /* .ó.ò.ïê....Øâ.ò. */
	$"979A 9A3D 02C6 5044 F547 0841 37D4 FFFE"            /* óöö=.∆PD.G.A7‘.. */
	$"FFFF 6F2C FC47 0545 4CAF CF6B 61F5 6308"            /* ..o,.G.ELØœka.c. */
	$"5E57 DBFF FEFF FF86 4DFC 6304 6167 BBD8"            /* ^W.....ÜM.c.agªÿ */
	$"A6F4 9E02 9B97 E9FD FF01 B490 FB9E 01A5"            /* ¶.û.õó....¥ê.û.• */
	$"CC00 00FF"                                          /* Ã... */
};

data 'PICT' (129, "weather") { /* gmail */
	$"0922 0000 0000 0020 0020 0011 02FF 0C00"            /* ∆"..... . ...... */
	$"FFFE 0000 0048 0000 0048 0000 0000 0000"            /* .....H...H...... */
	$"0020 0020 0000 0000 00A1 01F2 0016 3842"            /* . . .....°....8B */
	$"494D 0000 0000 0000 0020 0020 4772 8970"            /* IM....... . Grâp */
	$"68AF 626A 0001 000A 0000 0000 0020 0020"            /* hØbj......... .  */
	$"009A 0000 00FF 8080 0000 0000 0020 0020"            /* .ö....ÄÄ..... .  */
	$"0000 0004 0000 0000 0048 0000 0048 0000"            /* .........H...H.. */
	$"0010 0020 0003 0008 0000 0000 0000 0000"            /* ... ............ */
	$"0000 0000 0000 0000 0020 0020 0000 0000"            /* ......... . .... */
	$"0020 0020 0040 02A1 FF02 A1FF 02A1 FF02"            /* . . .@.°..°..°.. */
	$"A1FF 3E06 F8E2 E0E9 F5F3 F0F7 F1F9 F00E"            /* °.>............. */
	$"EFF2 F4E8 DEDF F8D4 6958 B0FF FFEE F0F8"            /* .......‘iX∞..... */
	$"F1FA F00F EFED FFFF AB4D 5ECF D05F 4DAB"            /* ........´M^œ–_M´ */
	$"FFFF EEF0 F8F1 FAF0 07EF EDFF FFA6 4154"            /* .............¶AT */
	$"CB46 08E1 DCDC D9E2 F0F2 EEEE F9EF FBEE"            /* ÀF.............. */
	$"FFED 0FF1 EFE0 D7D9 D8E0 5A4A 442E 7DF4"            /* ......◊.ÿ.ZJD.}. */
	$"FFEF EDF9 EFFB EE11 ECEE FFF3 7521 373C"            /* ............u!7< */
	$"4E4E 3E37 2074 F4FF F0ED F9EF FBEE 08EC"            /* NN>7 t.......... */
	$"EFFF F36C 122A 2F43 4A08 D9E5 DDDD D9DD"            /* ...l.*.CJ....... */
	$"ECF3 F0F9 EFFB EE12 EFF2 EBDC D7DA DAE8"            /* ............◊... */
	$"D54F 5452 4D2D 53CD FFF9 EDFA EFFC EE13"            /* ’OTRM-SÕ........ */
	$"ECF8 FFCB 4920 4247 4B43 4448 4741 1E47"            /* ...ÀI BGKCDHGA.G */
	$"CAFF F9ED FAEF FCEE 09EC F9FF C73D 1136"            /*  .......∆...«=.6 */
	$"3B3D 3754 09CF D3E5 DFDD DADA E6F2 F2FB"            /* ;=7T∆œ”......... */
	$"EFFB EEFF F113 E5D8 D8DB DDE8 D6AF 534E"            /* .......ÿÿ...÷ØSN */
	$"5251 5337 359C FFFF EDEE FDEF FDEE 17ED"            /* RQS75ú.......... */
	$"ECFF FF98 2B2C 4846 4A45 3C48 4246 4546"            /* ...ò+,HFJE<HBFEF */
	$"2927 95FF FFED EEFD EFFD EE0B EDEC FFFF"            /* )'ï............. */
	$"911C 1D3C 3A3E 392E 5A0A D7C3 C5E3 E3DC"            /* ë..<:>9.Z.◊√≈... */
	$"DCD9 E1EF F3FC EFFC EE17 F2EE E0D7 DADA"            /* .............◊.. */
	$"E0E5 C5A3 AF54 464A 504E 5244 296C E8FF"            /* ..≈£ØTFJPNRD)l.. */
	$"F2ED FEEF FEEE 19EC F1FF E766 203B 4A43"            /* ...........f ;JC */
	$"473F 2D38 483B 3E44 4147 3719 61E7 FFF2"            /* G?-8H;>DAG7.a... */
	$"EDFE EFFE EE0C ECF2 FFE6 5C10 2E3D 373C"            /* ..........\..=7< */
	$"331F 2860 0CD9 DAC0 B7DA E6DD DDD9 DCEA"            /* 3.(`...¿∑....... */
	$"F3F1 FEEF FEEE 4CF0 F2E9 DBD8 DBDC E1D7"            /* ......L....ÿ...◊ */
	$"B6A1 B0BA 544C 4447 4142 524E 2C44 BCFF"            /* ∂°∞∫TLDGABRN,Dº. */
	$"FDEC EFEF EEEE EBFC FFBA 3E25 464B 3634"            /* .........∫>%FK64 */
	$"3C2C 2F3C 483E 383D 3435 4542 1D37 B8FF"            /* <,/<H>8=45EB.7∏. */
	$"FEEC EFEF EEEE EBFD FFB6 3115 393E 2827"            /* .........∂1.9>(' */
	$"301C 1E2D 610E D7D6 DCC2 B3D0 E6E0 DDDB"            /* 0..-a.◊÷.¬≥–.... */
	$"D9E3 F1F3 EFFE EE4D F1F0 E3D9 DADC DEDD"            /* .......M........ */
	$"D0C8 ACB1 B3B7 534A 4356 9650 364D 5238"            /* –»¨±≥∑SJCVñP6MR8 */
	$"2B89 FEFF EEEE EDED FFFD 8727 334C 4627"            /* +â........á'3LF' */
	$"4BA7 4525 313C 473D 354B 9346 273F 452B"            /* KßE%1<G=5KìF'?E+ */
	$"1D82 FEFF EFEE EDED FFFE 7F17 2440 3817"            /* .Ç..........$@8. */
	$"41A4 3714 212C 615F D6D4 D3DE D4B1 C4E2"            /* A§7.!,a_÷‘”.‘±ƒ. */
	$"E4DD DBD8 DEED F3EE EEF2 ECDE D8DB DCE1"            /* ...ÿ........ÿ... */
	$"D7C7 D4E4 B9AE B2B7 534A 3D57 E8C6 6333"            /* ◊«‘.πÆ≤∑SJ=W.∆c3 */
	$"4351 4525 5BDA FFF2 F2FF D958 2241 4D3C"            /* CQE%[......X"AM< */
	$"2363 E7FA 3D22 313C 463C 2E4A E9C8 5B23"            /* #c..="1<F<.J.»[# */
	$"3646 3916 4FD8 FFF2 F2FF D74D 1234 402E"            /* 6F9.Oÿ....◊M.4@. */
	$"145B E8FB 2E11 212C 615F D6D4 D3D5 EBD9"            /* .[....!,a_÷‘”’.. */
	$"B0BA D8E5 DEDC D9DA E7F2 F2E7 DAD9 DCDE"            /* ∞∫ÿ............. */
	$"E1D0 C6D9 ECE2 B5AE B2B7 5249 3D51 E1F4"            /* .–∆...µÆ≤∑RI=Q.. */
	$"CE88 3C38 4D4E 2E37 A9FF FFA9 352B 4B4A"            /* Œà<8MN.7©..©5+KJ */
	$"2F30 93F7 FFD9 3A23 313C 463C 2E44 DFF6"            /* /0ì...:#1<F<.D.. */
	$"D184 2F29 4241 1E29 A3FF FFA3 271B 3E3D"            /* —Ñ/)BA.)£..£'.>= */
	$"1F22 8FFA FFD8 2B12 212C 615F D6D4 D3D5"            /* ."è..ÿ+.!,a_÷‘”’ */
	$"E2EB D9B4 B4CC E2E1 DBDA D8E3 E3D8 DADC"            /* ...¥¥Ã....ÿ..ÿ.. */
	$"E1DD C9C9 DFE7 E6E1 B5AE B3B8 5249 3C50"            /* ..……....µÆ≥∏RI<P */
	$"DAF4 DDD5 AC54 3047 503B 288D 8C27 394E"            /* ...’¨T0GP;(çå'9N */
	$"4326 4EC2 FFEB EEDB 3B23 313C 453B 2E44"            /* C&N¬....;#1<E;.D */
	$"DAF5 DED8 AC4A 2039 432D 1886 8619 2B41"            /* ...ÿ¨J 9C-.ÜÜ.+A */
	$"3516 44C1 FFEB F0DA 2C12 212C 615F D6D4"            /* 5.D¡....,.!,a_÷‘ */
	$"D3D5 E1E4 EAD9 B9B2 C2DB E4DC DBD9 D9DB"            /* ”’....π≤¬....... */
	$"DDE3 D6C5 D0E3 E3E1 E7E2 B5AE B3B8 5148"            /* ..÷≈–.....µÆ≥∏QH */
	$"3B4F DAEF E9D7 D0C7 7832 3B4E 482E 2D47"            /* ;O...◊–«x2;NH.-G */
	$"4D37 2979 E6FB E1E1 F1DB 3B23 313C 453B"            /* M7)y......;#1<E; */
	$"2E43 D9F0 E9D6 D2C9 7123 2C41 3B20 1F3B"            /* .C...÷“…q#,A; .; */
	$"4028 1A73 E8FD E1E0 F2DA 2B12 212C 612D"            /* @(.s......+.!,a- */
	$"D6D4 D3D5 E1E3 E3EA D7BB B6BC D1E3 DFDB"            /* ÷‘”’....◊ª∂º—... */
	$"DBE0 E0CD C5D8 E4E0 E1E2 E7E2 B5AE B3B8"            /* ...Õ≈ÿ......µÆ≥∏ */
	$"5047 3B4F DAEE E3EA D5C5 D89F 442F FE49"            /* PG;O....’≈ÿüD/.I */
	$"2E48 2C3D A8FA EEDD E1E2 F1DB 3A23 313C"            /* .H,=®.......:#1< */
	$"443A 2D43 D9EF E3EA D4C6 DB9D 371F 3B3D"            /* D:-C....‘∆.ù7.;= */
	$"3D3A 1C31 A6FD EFDD E1E2 F2DA 2B12 212C"            /* =:.1¶.......+.!, */
	$"615F D6D4 D3D5 E1E3 E2E3 EAD8 BEBF BCC8"            /* a_÷‘”’.....ÿæøº» */
	$"DEE2 E1DB C6C9 DEE2 DDE0 E1E2 E7E2 B5AE"            /* ....∆…........µÆ */
	$"B3B8 5047 3B4F DAEE E2E3 EAD6 BEDC C565"            /* ≥∏PG;O.....÷æ.≈e */
	$"2B41 4127 62D2 FCE2 DCE0 E1E2 F1DB 3B23"            /* +AA'b“........;# */
	$"313C 4339 2C42 D9EF E2E3 EAD6 BEDF C65C"            /* 1<C9,B.....÷æ.∆\ */
	$"1C34 3317 59D3 FFE2 DCE0 E1E2 F3DB 2B12"            /* .43.Y”........+. */
	$"212C 615F D6D4 D3D5 E1E3 E2E2 E3EA D9C1"            /* !,a_÷‘”’.......¡ */
	$"C6C0 C2D5 D4C4 D0E1 DFDD DFE1 E2E3 E8E2"            /* ∆¿¬’‘ƒ–......... */
	$"B5AF B4B8 5047 3A4E DAEE E2E2 E3EA D8BE"            /* µØ¥∏PG:N......ÿæ */
	$"D7DF 8D2F 2D90 EEF2 DCDC DFE1 E2E3 F2DC"            /* ◊.ç/-ê.......... */
	$"3A23 323C 4338 2C41 D9EF E2E2 E3EA D8BE"            /* :#2<C8,A......ÿæ */
	$"D9E1 8921 1E8B F1F3 DBDC DFE1 E2E3 F3DB"            /* ..â!.ã.......... */
	$"2B12 212C 6105 D6D4 D3D5 E1E3 FEE2 1CE3"            /* +.!,a.÷‘”’...... */
	$"E9DA C3C7 C5C5 CAD7 E0DC DDDE E0E1 E2E3"            /* ..√«≈≈ ◊........ */
	$"E8E3 B5AF B4B9 4F46 3A4E DAEE FEE2 1CE3"            /* ..µØ¥πOF:N...... */
	$"E9DA C1CC E3A8 ADF6 E5DA DDDE E0E1 E2E3"            /* ..¡Ã.®≠......... */
	$"F3DC 3A23 323C 4238 2B41 D9EF FEE2 16E3"            /* ..:#2<B8+A...... */
	$"E9DA C1CC E6A5 ABF8 E6DA DDDE E0E1 E2E3"            /* ..¡Ã.•´......... */
	$"F4DB 2B12 212B 5B05 D5D3 D2D4 E1E3 FCE2"            /* ..+.!+[.’”“‘.... */
	$"1AE9 D9C2 D0DC DDDC DCDD DDDF E0E1 E3E4"            /* ...¬–........... */
	$"E9E3 B5B0 B4B9 4E45 394D DAEE FCE2 1AE9"            /* ..µ∞¥πNE9M...... */
	$"D9C2 CEEE F0DA DBDD DDDF E0E1 E3E4 F3DD"            /* .¬Œ............. */
	$"3A24 323C 4137 2A40 D9EF FCE2 14E9 D9C2"            /* :$2<A7*@.......¬ */
	$"CDF0 F2DA DBDD DDDF E0E1 E3E4 F4DC 2B12"            /* Õ.............+. */
	$"212B 5B05 D5D3 D2D4 E1E3 FCE2 1AE0 E7E4"            /* !+[.’”“‘........ */
	$"D7D9 DADC DCDD DFE0 E1E2 E3E4 E9E3 B6B0"            /* ◊.............∂∞ */
	$"B4B9 4E45 394C DAEE FCE2 1AE0 E7E4 D7D9"            /* ¥πNE9L........◊. */
	$"DADC DCDD DFE0 E1E2 E3E4 F3DD 3A24 313C"            /* ............:$1< */
	$"4137 2A40 D9EF FCE2 14E0 E7E4 D7D9 DADC"            /* A7*@........◊... */
	$"DCDD DFE0 E1E2 E3E4 F5DC 2B12 202B 5E05"            /* ..........+. +^. */
	$"D5D3 D2D4 E1E3 FDE2 1BDF E3EE F6E8 D7D9"            /* ’”“‘..........◊. */
	$"DCDD DEE0 E0E2 E3E4 E5EA E4B6 B0B5 B94E"            /* ...........∂∞µπN */
	$"4438 4CDA EEFD E21B DFE3 EEF6 E8D7 D9DC"            /* D8L..........◊.. */
	$"DDDE E0E0 E2E3 E4E5 F4DD 3B23 313C 4137"            /* ..........;#1<A7 */
	$"2A40 D9EF FDE2 15DF E3EE F6E8 D7D9 DCDD"            /* *@..........◊... */
	$"DEE0 E0E2 E3E4 E5F5 DD2C 1120 2B61 5FD5"            /* .........,. +a_’ */
	$"D3D2 D4E1 E3E2 E2E1 DFE6 F0F0 EEF3 E8D9"            /* ”“‘............. */
	$"DADE DFE0 E1E3 E4E4 E6EA E4B6 B0B5 B94E"            /* ...........∂∞µπN */
	$"4438 4CDA EEE2 E2E1 DFE6 F0F0 EEF3 E8D9"            /* D8L............. */
	$"DADE DFE0 E1E3 E4E4 E6F5 DE3B 2331 3C41"            /* ...........;#1<A */
	$"3729 3FD9 EFE2 E2E1 DFE6 F0F0 EEF3 E8D9"            /* 7)?............. */
	$"DADE DFE0 E1E3 E4E4 E6F6 DD2B 1020 2B61"            /* ...........+. +a */
	$"0BD5 D3D2 D4E1 E3E2 E0E0 EAF1 EFFE EE1C"            /* .’”“‘........... */
	$"F2E9 DBDE E0E1 E2E3 E4E5 E6EB E4B7 B1B5"            /* .............∑±µ */
	$"B94E 4437 4CDA EEE2 E0E0 EAF1 EFFE EE1C"            /* πND7L........... */
	$"F2E9 DBDE E0E1 E2E3 E4E5 E6F5 DE3B 2331"            /* .............;#1 */
	$"3C40 3629 3FD9 EFE2 E0E0 EAF1 EFFE EE10"            /* <@6)?........... */
	$"F2E9 DBDE E0E1 E2E3 E4E5 E6F6 DD2A 1120"            /* .............*.  */
	$"2B58 09D5 D3D2 D4E1 E3DF E2EC F1FB EE19"            /* +X∆’”“‘......... */
	$"F2EA DEE0 E2E3 E4E5 E6E7 EBE4 B7B1 B5B9"            /* ............∑±µπ */
	$"4D43 374B DAEE DFE2 ECF1 FBEE 19F2 EADE"            /* MC7K............ */
	$"E0E2 E3E4 E5E6 E7F5 DE3A 2331 3C3F 3528"            /* .........:#1<?5( */
	$"3ED9 EFDF E2EC F1FB EE0F F2EA DEE0 E2E3"            /* >............... */
	$"E4E5 E6E7 F7DD 2A11 202B 5208 D5D2 D2D4"            /* ......*. +R.’““‘ */
	$"E0E0 E4EF F1F9 EE17 F1EA DFE2 E4E5 E6E6"            /* ................ */
	$"E7EB E4B8 B1B5 B846 4337 4BD9 EBE4 EFF1"            /* ...∏±µ∏FC7K..... */
	$"F9EE 17F1 EADF E2E4 E5E6 E6E7 F5DE 3A23"            /* ..............:# */
	$"3134 3835 283E D8EC E4EF F1F9 EE0E F1EA"            /* 1485(>ÿ......... */
	$"DFE2 E4E5 E6E6 E7F7 DD2A 1120 244F 08D2"            /* .........*. $O.“ */
	$"DCD6 D7E2 ECF4 F4F1 F8F2 16F5 EFE6 E7E9"            /* .÷◊............. */
	$"EAEB EBEF E9BB B4BC B546 4537 4BDA F7F4"            /* .....ª¥ºµFE7K... */
	$"F4F1 F8F2 16F5 EFE6 E7E9 EAEB EBF9 E23C"            /* ...............< */
	$"2333 3639 3728 3DD9 F9F4 F4F1 F8F2 0DF5"            /* #3697(=.......¬. */
	$"EFE6 E7E9 EAEB EBFA E12B 1022 2546 06E8"            /* .........+."%F.. */
	$"D3D0 D0E3 EDE9 F5E8 03EB E5E0 E1FE E20C"            /* ”––............. */
	$"E5E1 B7B1 B9E1 BF58 3F50 DDF7 E9F5 E803"            /* ..∑±π.øX?P...... */
	$"EBE5 E0E1 FEE2 0CEF DA43 2D4A BBBB 4D31"            /* .........C-JªªM1 */
	$"44DC F8E9 F5E8 03EB E5E0 E1FE E205 F1DA"            /* D............... */
	$"341C 3CB6 02A1 FF02 A1FF 02A1 FF02 A1FF"            /* 4.<∂.°..°..°..°. */
	$"00FF"                                               /* .. */
};

data 'PICT' (130, "bw-facebook") {
	$"00D0 0000 0000 0020 0020 1101 A101 F200"            /* .–..... . ..°... */
	$"1638 4249 4D00 0000 0000 0000 2000 2047"            /* .8BIM....... . G */
	$"7289 7068 AF62 6A01 000A 0000 0000 0020"            /* râphØbj........  */
	$"0020 9000 0400 0000 0000 2000 2000 0000"            /* . ê....... . ... */
	$"0000 2000 2000 0000 0000 2000 2000 007F"            /* .. . ..... . ... */
	$"FFFF FEFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ................ */
	$"FFFF FFFF FFF0 1FFF FFE0 1FFF FFC0 1FFF"            /* .............¿.. */
	$"FFC0 1FFF FF81 FFFF FF83 FFFF FF83 FFFF"            /* .¿...Å...É...É.. */
	$"FF83 FFFF FF83 FFFF FF83 FFFF F800 1FFF"            /* .É...É...É...... */
	$"F800 1FFF F800 3FFF F800 3FFF F800 3FFF"            /* ......?...?...?. */
	$"FF83 FFFF FF83 FFFF FF83 FFFF FF83 FFFF"            /* .É...É...É...É.. */
	$"FF83 FFFF FF83 FFFF FF83 FFFF FF83 FFFF"            /* .É...É...É...É.. */
	$"FF83 FFFF FF83 FFFF FF83 FF7F FF83 FEFF"            /* .É...É...É...É.. */
};

data 'PICT' (131, "bw-weather") { /* gmail */
	$"00D0 0000 0000 0020 0020 1101 A101 F200"            /* .–..... . ..°... */
	$"1638 4249 4D00 0000 0000 0000 2000 2047"            /* .8BIM....... . G */
	$"7289 7068 AF62 6A01 000A 0000 0000 0020"            /* râphØbj........  */
	$"0020 9000 0400 0000 0000 2000 2000 0000"            /* . ê....... . ... */
	$"0000 2000 2000 0000 0000 2000 2000 0000"            /* .. . ..... . ... */
	$"0000 0000 0000 0000 0000 0000 0000 007F"            /* ................ */
	$"FFFF FEF8 0000 1FFC 0000 3FFE 0000 7FFF"            /* ..........?..... */
	$"0000 FFFF 8001 FFE7 C003 F7E3 E007 EFE1"            /* ....Ä...¿....... */
	$"F00F D7E0 F81F AFE0 7C3F 57E0 3FFE AFE0"            /* ..◊...Ø.|?W.?.Ø. */
	$"1FFD 57E0 0FFA AFE0 07F5 57E0 03EA AFE0"            /* ..W...Ø...W...Ø. */
	$"0155 57E0 00AA AFE0 0055 57E0 002A AFE0"            /* .UW..™Ø..UW..*Ø. */
	$"0015 57E0 000A AFE0 0005 577F FFFF FE00"            /* ..W...Ø...W..... */
	$"0000 0000 0000 0000 0000 0000 0000 00FF"            /* ................ */
};