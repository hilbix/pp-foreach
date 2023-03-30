# This Works is placed under the terms of the Copyright Less License,
# see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.
# Read: Free as in free beer, free speech and free baby

BEGIN	{
	printf "/* automatically generated from %s, DO NOT EDIT! */\n\n", GEN;
	printf "#define PP_DEC(x) PP_CAT_(PP_DEC_,x)\n"
	printf "#define PP_INC(x) PP_CAT_(PP_INC_,x)\n"
	printf "#define PP_NUM(x) PP_CHECK(PP_CAT_(PP_NUM_,x))\n"
	for (i=0; i<=MAX; i++)
	  {
	    j=i-1; if (j<0) j=0;
	    k=i+1; if (j>MAX) j=MAX;
	    printf "#define PP_DEC_%d %d\n", i, j;
	    printf "#define PP_INC_%d %d\n", i, k;
	    printf "#define PP_NUM_%d PP_PROBE(@)\n", i, k;
	  }
	}

