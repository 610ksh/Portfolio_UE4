#pragma once

#define SH_CheckNull(p) { if(p==NULL) return; }
#define CheckNullResult_SH(p, result) { if(p==NULL) return result; }

#define SH_CheckTrue(p) { if(p == true) return;}
#define CheckTrueResult_SH(p, result) { if(p==true) return result; }

#define SH_CheckFalse(p) { if(p == false) return;}
#define CheckFalseResult_SH(p, result) { if(p==false) return result; }