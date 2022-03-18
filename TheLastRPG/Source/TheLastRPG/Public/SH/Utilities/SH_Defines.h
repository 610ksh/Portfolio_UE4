#pragma once

#define CheckNull_SH(p) { if(p==NULL) return; }
#define CheckNullResult_SH(p, result) { if(p==NULL) return result; }

#define CheckTrue_SH(p) { if(p == true) return;}
#define CheckTrueResult_SH(p, result) { if(p==true) return result; }

#define CheckFalse_SH(p) { if(p == false) return;}
#define CheckFalseResult_SH(p, result) { if(p==false) return result; }