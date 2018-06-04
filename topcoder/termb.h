#ifdef TERMB_EXPORTS
#define TERMB_API //__declspec(dllexport)
#else
#define TERMB_API __declspec(dllimport)
#endif



#ifdef __cplusplus
extern "C"
{
#endif

TERMB_API int __stdcall InitComm(int Port);
TERMB_API int __stdcall InitCommExt();
TERMB_API int __stdcall CloseComm();
TERMB_API int __stdcall Authenticate();
TERMB_API int __stdcall Read_Content(int Active);

TERMB_API int __stdcall GetSAMID(char *SAMID);

TERMB_API int __stdcall GetBmpPhoto(const char* pszPath);

TERMB_API int __stdcall Reset_SAM();

TERMB_API int __stdcall GetSAMStatus();

#ifdef __cplusplus
}
#endif