namespace winutil {
	
	// Formats a windows error into a C++ string.
	inline std::string FormatWindowsError() noexcept {
		char* buffer = new char[512]; // excessive
		DWORD error = GetLastError();
		
		if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buffer, 512, NULL) == 0) {
			delete[] buffer;
			return std::string("Error formatting message");
		} else {
			return std::string(buffer);
		}
	}	
	
}