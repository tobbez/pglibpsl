#include "postgres.h"
#include "fmgr.h"
#include "mb/pg_wchar.h"
#include "utils/builtins.h"

#include "libpsl.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(psl_regdomain);

Datum psl_regdomain(PG_FUNCTION_ARGS) {
  text *name = PG_GETARG_TEXT_PP(0);
  char *name_cstr = text_to_cstring(name);
  char *name_normalized;
  const psl_ctx_t *psl = psl_builtin();
  char *regdomain;
  text *regdomain_text;

  if (psl_str_to_utf8lower(name_cstr, GetDatabaseEncodingName(), NULL, &name_normalized) != PSL_SUCCESS) {
    ereport(ERROR, (errmsg_internal("Failed to normalize name %s", name_cstr)));
    PG_RETURN_VOID();
  }

  /* if not NULL, regdomain is a pointer into name_normalized (so should not be freed) */
  regdomain = (char*)psl_registrable_domain(psl, name_normalized);

  if (!regdomain) {
    psl_free_string(name_normalized);
    PG_RETURN_NULL();
  }

  regdomain_text = cstring_to_text(regdomain);

  psl_free_string(name_normalized);

  PG_RETURN_TEXT_P(regdomain_text);
}
