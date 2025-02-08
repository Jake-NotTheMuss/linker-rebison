
CC= x86_64-w64-mingw32-g++

src= rebison.cc lex.cc icmp.c xmalloc.c cmd.cc
hdr= rebison.h lex.hh array.hh

REBISON=html/rebison scr/rebison scr_sym/rebison sproc/rebison

scr_data=scr/symbol.h scr/tables.h scr/token.h scr/yycheck.c scr/yydefact.c \
	scr/yydefgoto.c scr/yypact.c scr/yypgoto.c scr/yyr1.c scr/yyr2.c \
	scr/yytable.c scr/yytname.c scr/yytranslate.c

scr_sym_data=scr_sym/symbol.h scr_sym/tables.h scr_sym/token.h \
	scr_sym/yycheck.c scr_sym/yydefact.c scr_sym/yydefgoto.c scr_sym/yypact.c \
	scr_sym/yypgoto.c scr_sym/yyr1.c scr_sym/yyr2.c scr_sym/yytable.c \
	scr_sym/yytname.c scr_sym/yytranslate.c

html_data=html/symbol.h html/tables.h html/token.h html/yycheck.c \
	html/yydefact.c html/yydefgoto.c html/yypact.c html/yypgoto.c \
	html/yyr1.c html/yyr2.c html/yytable.c html/yytname.c \
	html/yytranslate.c

all: $(REBISON)

scr/rebison: scr_data.h $(scr_data)

scr_sym/rebison: scr_sym_data.h $(scr_sym_data)

sproc/rebison: sproc_data.h $(sproc_data)

$(REBISON): $(hdr) $(src)
	t=$@; dir=$${t%%/*}; hdr=$${dir}_data.h; \
	$(CC) $(CFLAGS) -xc++ -DDATA_HEADER='"'$$hdr'"' -g -o $@ $(src) \
	$${dir}/yytable.c \
	$${dir}/yydefact.c $${dir}/yypact.c $${dir}/yydefgoto.c \
	$${dir}/yypgoto.c $${dir}/yycheck.c $${dir}/yyr1.c $${dir}/yyr2.c \
	$${dir}/yytname.c $${dir}/yytranslate.c

clean:
	rm -f $(REBISON)

.PHONY: all clean
