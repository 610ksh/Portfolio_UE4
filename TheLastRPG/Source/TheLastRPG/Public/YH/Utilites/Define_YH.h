#pragma once

#define YH_CheckNull(p){ if(p == NULL) return ; }
#define YH_CheckNullResult(p, result){ if(p == NULL) return result;}

#define YH_CheckTrue(p){ if(p == true) return ; }
#define YH_CheckTrueResult(p, result){ if(p == true) return result; }

#define YH_CheckFalse(p){ if(p == false) return ; }
#define YH_CheckFalseResult(p, result){ if(p == false) return result; }