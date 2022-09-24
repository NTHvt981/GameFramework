//class CSoundManager
//{
//protected:
//    LPDIRECTSOUND8 m_pDS;
//
//public:
//    CSoundManager();
//    ~CSoundManager();
//
//    HRESULT Initialize(HWND hWnd, DWORD dwCoopLevel);
//    inline  LPDIRECTSOUND8 GetDirectSound() { return m_pDS; }
//    HRESULT SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate);
//
//    HRESULT Create(
//		CSound** ppSound, 
//		LPTSTR strWaveFileName, 
//		DWORD dwCreationFlags = 0, 
//		GUID guid3DAlgorithm = GUID_NULL, 
//		DWORD dwNumBuffers = 1);
//};