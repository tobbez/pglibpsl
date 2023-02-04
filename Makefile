# Need to use MODULE_big instead of MODULES for SHLIB_LINK to be honoured
# https://www.postgresql.org/message-id/CABRT9RAnPw+O5RPUnT=fJs5yvMYN6w0XQNXsjDD=KNzfgL=jQg@mail.gmail.com
# https://www.postgresql.org/message-id/1331244245.1197.27.camel%40vanquo.pezone.net
MODULE_big = pglibpsl
OBJS = pglibpsl.o

EXTENSION = pglibpsl
DATA = pglibpsl--0.1.0.sql
PGFILEDESC = "Query the Public Suffix List using libpsl"

SHLIB_LINK = -lpsl

REGRESS = psl_regdomain

PG_CONFIG ?= pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
