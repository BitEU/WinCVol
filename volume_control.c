#include <stdio.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <conio.h>
#include <initguid.h>
#include <functiondiscoverykeys_devpkey.h>

// Define min/max macros
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

// Define the GUIDs we need
DEFINE_GUID(CLSID_MMDeviceEnumerator, 0xbcde0395, 0xe52f, 0x467c, 0x8e, 0x3d, 0xc4, 0x57, 0x92, 0x91, 0x69, 0x2e);
DEFINE_GUID(IID_IMMDeviceEnumerator, 0xa95664d2, 0x9614, 0x4f35, 0xa7, 0x46, 0xde, 0x8d, 0xb6, 0x36, 0x17, 0xe6);
DEFINE_GUID(IID_IAudioEndpointVolume, 0x5cdf2c82, 0x841e, 0x4546, 0x97, 0x22, 0x0c, 0xf7, 0x40, 0x78, 0x22, 0x9a);

// Function to print text at a specific console coordinate
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to draw the TUI
void draw_ui(float current_volume) {
    system("cls");
    printf("Windows Master Volume Control\n");
    printf("=============================\n\n");
    printf("Use '+' to increase volume, '-' to decrease.\n");
    printf("Press number keys: 0=0%%, 1=10%%, 2=20%%, 3=30%%, 4=40%%, 5=50%%\n");
    printf("                   6=60%%, 7=70%%, 8=80%%, 9=90%%\n");
    printf("Press 'q' to quit.\n\n");

    // Draw a volume bar
    printf("Current Volume: [");
    int bar_width = 50;
    int filled_width = (int)(current_volume * bar_width);
    for (int i = 0; i < bar_width; ++i) {
        if (i < filled_width) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("] %.0f%%\n", current_volume * 100);
}

int main() {
    HRESULT hr;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    IAudioEndpointVolume *pEndpointVolume = NULL;
    float current_volume = 0.0f;

    // Initialize COM
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        printf("Failed to initialize COM: 0x%08x\n", hr);
        return 1;
    }

    // Create a device enumerator
    hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (void**)&pEnumerator);
    if (FAILED(hr)) {
        printf("Failed to create device enumerator: 0x%08x\n", hr);
        CoUninitialize();
        return 1;
    }

    // Get the default audio endpoint
    hr = pEnumerator->lpVtbl->GetDefaultAudioEndpoint(pEnumerator, eRender, eConsole, &pDevice);
    if (FAILED(hr)) {
        printf("Failed to get default audio endpoint: 0x%08x\n", hr);
        pEnumerator->lpVtbl->Release(pEnumerator);
        CoUninitialize();
        return 1;
    }

    // Activate the audio endpoint volume interface
    hr = pDevice->lpVtbl->Activate(pDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (void**)&pEndpointVolume);
    if (FAILED(hr)) {
        printf("Failed to activate endpoint volume: 0x%08x\n", hr);
        pDevice->lpVtbl->Release(pDevice);
        pEnumerator->lpVtbl->Release(pEnumerator);
        CoUninitialize();
        return 1;
    }

    // Main loop to handle user input
    char ch;
    do {
        // Get the current volume
        hr = pEndpointVolume->lpVtbl->GetMasterVolumeLevelScalar(pEndpointVolume, &current_volume);
        if (FAILED(hr)) {
            printf("Failed to get master volume: 0x%08x\n", hr);
            break;
        }

        draw_ui(current_volume);

        ch = _getch();

        switch (ch) {
            case '+':
            case '=':
                // Increase volume by 5%
                pEndpointVolume->lpVtbl->GetMasterVolumeLevelScalar(pEndpointVolume, &current_volume);
                current_volume = min(1.0f, current_volume + 0.05f);
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, current_volume, NULL);
                break;
            case '-':
                // Decrease volume by 5%
                pEndpointVolume->lpVtbl->GetMasterVolumeLevelScalar(pEndpointVolume, &current_volume);
                current_volume = max(0.0f, current_volume - 0.05f);
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, current_volume, NULL);
                break;
            case '0':
                // Set volume to 0%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.0f, NULL);
                break;
            case '1':
                // Set volume to 10%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.1f, NULL);
                break;
            case '2':
                // Set volume to 20%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.2f, NULL);
                break;
            case '3':
                // Set volume to 30%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.3f, NULL);
                break;
            case '4':
                // Set volume to 40%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.4f, NULL);
                break;
            case '5':
                // Set volume to 50%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.5f, NULL);
                break;
            case '6':
                // Set volume to 60%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.6f, NULL);
                break;
            case '7':
                // Set volume to 70%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.7f, NULL);
                break;
            case '8':
                // Set volume to 80%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.8f, NULL);
                break;
            case '9':
                // Set volume to 90%
                pEndpointVolume->lpVtbl->SetMasterVolumeLevelScalar(pEndpointVolume, 0.9f, NULL);
                break;
        }

    } while (ch != 'q' && ch != 'Q');

    // Clean up
    pEndpointVolume->lpVtbl->Release(pEndpointVolume);
    pDevice->lpVtbl->Release(pDevice);
    pEnumerator->lpVtbl->Release(pEnumerator);
    CoUninitialize();

    system("cls");
    printf("Exited.\n");

    return 0;
}
