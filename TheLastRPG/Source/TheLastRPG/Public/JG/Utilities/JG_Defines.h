#pragma once

#define JG_CheckNull(p) { if(p==NULL) return; }
#define JG_CheckNullResult(p, result) { if(p==NULL) return result; }

#define JG_CheckTrue(p) { if(p == true) return;}
#define JG_CheckTrueResult(p, result) { if(p==true) return result; }

#define JG_CheckFalse(p) { if(p == false) return;}
#define JG_CheckFalseResult(p, result) { if(p==false) return result; }