namespace winutil {
	
	class Window {
		WNDPROC m_WndProc = NULL;
		WNDCLASSEX m_Class;
		HINSTANCE m_Instance = NULL;
		HWND m_Window = NULL;
		bool m_Created = false;
		std::string m_Title = "";
		std::string m_ClassName = "";
		int m_Width = 0;
		int m_Height = 0;
	public:
		inline Window() {}
		
		inline Window(WNDPROC wndproc, std::string const &title, int w, int h, std::string const &class_name,
					  HINSTANCE instance) : 
					  m_WndProc(wndproc), m_Title(title), m_ClassName(class_name), m_Instance(instance), m_Width(w), m_Height(h) {
		}
		
		inline void Initalize() {
			// Create the window class and register it
			m_Class.cbSize = sizeof(WNDCLASSEX);
			m_Class.style = 0;
			m_Class.lpfnWndProc = m_WndProc;
			m_Class.cbClsExtra = 0;
			m_Class.cbWndExtra = 0;
			m_Class.hInstance = m_Instance;
			m_Class.hIcon = NULL;
			m_Class.hCursor = LoadCursor(NULL, IDC_ARROW);
			m_Class.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
			m_Class.lpszMenuName  = NULL;
			m_Class.lpszClassName = m_ClassName.c_str();
			m_Class.hIconSm = NULL;
				
			if(!RegisterClassEx(&m_Class)) {
				throw std::runtime_error("Windows error " + std::to_string(GetLastError()) + ": " + FormatWindowsError());
			}
				
			// Create the actual window.
			m_Window = CreateWindowExA(WS_EX_CLIENTEDGE,m_ClassName.c_str(), 
									m_Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
									CW_USEDEFAULT, m_Width, m_Height, 
									NULL, NULL, m_Instance, NULL);
										
			if(!m_Window) {
				throw std::runtime_error("Windows error " + std::to_string(GetLastError()) + ": " + FormatWindowsError());
			}
			
			ShowWindow(m_Window, SW_SHOW);
			UpdateWindow(m_Window);
			m_Created = true;

		}
		
		inline void BeginMessageLoop() {
			if(m_Created) {
				MSG WindowMessage;
				while(GetMessage(&WindowMessage, NULL, 0, 0) > 0){
					TranslateMessage(&WindowMessage);
					DispatchMessage(&WindowMessage);
				}
			}
		}
		
		inline HWND GetHwnd() { 
			if(m_Window) return m_Window;
			return NULL;
		}
	};
	
}