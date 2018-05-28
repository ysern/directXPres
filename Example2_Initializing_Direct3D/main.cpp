//Include necessary Headers//
#include <windows.h>
#include <d3d9.h>

//Include the Direct3D library
#pragma comment (lib, "d3d9.lib")

//Define variables/constants//
LPCTSTR WndClassName = "firstwindow";    //Define our window class name
HWND hwnd = NULL;    //Sets our windows handle to NULL

const int Width = 800;    //window width
const int Height = 600;    //window height

						   //Pointer to Direct3D interface
IDirect3D9* d3d9 = NULL;

//pointer to Direct3D device class
IDirect3DDevice9* d3dDevice = NULL;

//Functions//
bool SetupScene();    //Set up our Scene
void CleanUpScene(); //Release memory
bool RenderScene(); //Renders a single frame

					//Initialize window and Direct3D
bool InitializeD3DWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** d3dDevice);

//Main part of the program
int messageloop(bool(*display)(float timeDelta));

//Windows callback procedure, handles messages
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);



bool SetupScene() {    //Set up our Scene

	return true;
}

void CleanUpScene() {    //Release memory

	return;
}

bool RenderScene(float timeDelta)    //Renders a single frame
{
	if (d3dDevice)
	{
		//Clear the window to 0x00000000 (black)
		d3dDevice->Clear(0, 0,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			0x00000055, 1.0f, 0);

		//Start drawing our scene
		d3dDevice->BeginScene();

		//Stop drawing our scene
		d3dDevice->EndScene();

		//Display our newly created scene
		d3dDevice->Present(0, 0, 0, 0);
	}
	return true;
}

//Main windows function
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//Initialize Direct3D//    
	//If initialization failed, display an error message
	if (!InitializeD3DWindow(hInstance, nShowCmd,
		Width, Height,
		true,
		D3DDEVTYPE_HAL,
		&d3dDevice))
	{
		// If initialization failed, display an error message
		MessageBox(0, "Window/D3D Initialization - Failed",
			"Error", MB_OK);
		return 0;
	}
	//Setup our scene
	if (!SetupScene())
	{
		// If Setup failed, display error message
		MessageBox(0, "SetupScene() - FAILED", 0, 0);
		return 0;
	}

	//Jump into the heart of our program
	messageloop(RenderScene);

	//Release memory allocated by our SetupScene function
	CleanUpScene();

	d3dDevice->Release();    //Release our Direct3D Device

	return 0;
}

//Initialize our Direct3D window
bool InitializeD3DWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** d3dDevice)
{
	//Start creating the window//

	WNDCLASSEX wc;    //Create a new extended windows class

	wc.cbSize = sizeof(WNDCLASSEX);    //Size of our windows class
	wc.style = CS_HREDRAW | CS_VREDRAW;    //class styles
	wc.lpfnWndProc = WndProc;    //Default windows procedure function
	wc.cbClsExtra = NULL;    //Extra bytes after our wc structure
	wc.cbWndExtra = NULL;    //Extra bytes after our windows instance
	wc.hInstance = hInstance;    //Instance to current application
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);    //Title bar Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);    //Default mouse Icon
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);    //Window bg color
	wc.lpszMenuName = NULL;    //Name of the menu attached to our window
	wc.lpszClassName = WndClassName;    //Name of our windows class
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); //Icon in your taskbar

	if (!RegisterClassEx(&wc))    //Register our windows class
	{
		//If registration failed, display error
		MessageBox(NULL, "Error registering class",
			"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	HWND hwnd = CreateWindowEx(    //Create our Extended Window
		NULL,    //Extended style
		WndClassName,    //Name of our windows class
		"Window Title",    //Name in the title bar of our window
		WS_OVERLAPPEDWINDOW,    //style of our window
		CW_USEDEFAULT, CW_USEDEFAULT,    //Top left corner of window
		width,    //Width of our window
		height,    //Height of our window
		NULL,    //Handle to parent window
		NULL,    //Handle to a Menu
		hInstance,    //Specifies instance of current program
		NULL    //used for an MDI client window
	);

	if (!hwnd)    //Make sure our window has been created
	{
		//If not, display error
		MessageBox(NULL, "Error creating window",
			"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, ShowWnd);    //Shows our window
	UpdateWindow(hwnd);    //Its good to update our window

						   //Start initializing Direct3D//

						   //Start by initializing the Direct3D interface
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d9) {    //If it was not initialized
		return false;
	}

	D3DCAPS9 caps;    //Set the device capabilities structure to caps

					  //Get the device capabilities
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vertexproc = NULL;    //Set our vertex processing to NULL

							  //If we can use hardware vertex processing
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		//Set vertex processing to hardware
		vertexproc = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		//Set vertex processing to software
		vertexproc = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;

	//The width of the back buffer in pixels
	d3dpp.BackBufferWidth = width;

	//The height of the back buffer in pixels    
	d3dpp.BackBufferHeight = height;

	//Back buffer pixel format
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	//Amount of back buffers
	d3dpp.BackBufferCount = 1;

	//The type of multisampling for the buffer
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

	//The quality of multisampling
	d3dpp.MultiSampleQuality = NULL;

	//Specifies how buffers will be swapped
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//Handle to our window
	d3dpp.hDeviceWindow = hwnd;

	//FullScreen or Windowed
	d3dpp.Windowed = windowed;

	//true lets Direct3D do the depth/stencil buffer automatically
	d3dpp.EnableAutoDepthStencil = true;

	//Auto depth/stencil buffer format
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//Additional characteristics
	d3dpp.Flags = NULL;

	//Refresh rate
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	//Presentation Interval
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = 0;

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type
		hwnd,               // window associated with device
		vertexproc,         // vertex processing
		&d3dpp,             // present parameters
		d3dDevice);         // return created device

	if (FAILED(hr))    //If there was a problem creating the device
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vertexproc,
			&d3dpp,
			d3dDevice);

		if (FAILED(hr))    //If it still fails
		{
			d3d9->Release(); // done with d3d9 object
			d3d9 = NULL;
			MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release(); // done with d3d9 object
	d3d9 = NULL;
	
	return true;    //If there were no errors, return true
}

int messageloop(bool(*display)(float timeDelta)) {    //The message loop

	MSG msg;    //Create a new message structure
	ZeroMemory(&msg, sizeof(MSG));    //clear message structure to NULL

									  //Set the last time. Keeps track of time between frames
	static float lastTime = (float)timeGetTime();

	while (TRUE)    //While there is a message
	{
		//If there was a windows message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)    //If the message was WM_QUIT
				break;    //Exit the message loop

			TranslateMessage(&msg);    //Translate the message
									   //Send the message to default windows procedure
			DispatchMessage(&msg);
		}

		else {    //Otherewise, keep the flow going

				  //Set the time
			float currTime = (float)timeGetTime();

			//Set the speed until the next frame
			float timeDelta = (currTime - lastTime)*0.001f;

			display(timeDelta);    //Display the goods

								   //Last time equal to current time
			lastTime = currTime;

		}


	}

	if (d3d9) {    //If there is a Direct3D device
		d3d9->Release();    //Release Memory from the device
		d3d9 = NULL;        //Make sure there is no memory leaks
	}

	return (int)msg.wParam;        //Return the message

}

LRESULT CALLBACK WndProc(HWND hwnd,        //Default windows procedure
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)    //Check message
	{
	case WM_KEYDOWN:    //For a key down

						//If escape key was pressed, display popup box
		if (wParam == VK_ESCAPE) {
			if (MessageBox(0, "Are you sure you want to exit?",
				"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				//Release the windows allocated memory
				DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:    //If x button in top right was pressed
		PostQuitMessage(0);
		return 0;
	}
	//return the message for windows to handle it
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}