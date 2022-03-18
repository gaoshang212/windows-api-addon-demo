#include <node.h>
#include <v8.h>
#include <nan.h>
#include <node_api.h>
#include <map>
#include <Windows.h>

using namespace v8;

std::string GBKToUtf8(std::string str)
{
    auto strGBK = str.c_str();
    int len = MultiByteToWideChar(CP_ACP, 0, (LPCCH)strGBK, -1, NULL, 0);
    unsigned short *wszUtf8 = new unsigned short[len + 1];
    memset(wszUtf8, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, (LPCCH)strGBK, -1, (LPWSTR)wszUtf8, len);
    len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
    char *szUtf8 = new char[len + 1];
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, (LPSTR)szUtf8, len, NULL, NULL);
    std::string result = szUtf8;
    delete[] szUtf8;
    delete[] wszUtf8;

    return result;
}

static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam)
{
    int length = GetWindowTextLength(hWnd);
    char *buffer = new char[length + 1];
    GetWindowText(hWnd, buffer, length + 1);
    std::string windowTitle(buffer);

    if (IsWindowVisible(hWnd) && length != 0)
    {
        std::map<std::string, HWND> *windowList = (std::map<std::string, HWND> *)lparam;
        (*windowList)[windowTitle] = hWnd;
    }

    return TRUE;
}

void Method(const Nan::FunctionCallbackInfo<v8::Value> &args)
{
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();

    std::map<std::string, HWND> *list = new std::map<std::string, HWND>();
    EnumWindows(enumWindowCallback, (LPARAM)list);

    Local<Array> result = Nan::New<Array>();
    for (auto it = list->begin(); it != list->end(); ++it)
    {
        auto title = Nan::New(GBKToUtf8(it->first)).ToLocalChecked();
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, Nan::New("title").ToLocalChecked(), title);
        Nan::Set(obj, Nan::New("handle").ToLocalChecked(), Nan::New<v8::Number>((uint64_t)it->second));
        Nan::Set(result, result->Length(), obj);
    }

    args.GetReturnValue().Set(result.As<v8::Value>());
}

void init(v8::Local<v8::Object> exports)
{
    v8::Local<v8::Context> context = exports->CreationContext();
    exports->Set(context, Nan::New("EnumWindows").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(Method)->GetFunction(context).ToLocalChecked());
}

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(binding, init)
#else
NODE_MODULE(binding, init);
#endif