#ifndef _WEBSOCKET_PROTOCOL_H_
#define _WEBSOCKET_PROTOCOL_H_


#include "protocol.h"

#include <web_socket.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <esp_timer.h>

#include <memory>
#include <atomic>

#define WEBSOCKET_PROTOCOL_SERVER_HELLO_EVENT (1 << 0)

class WebsocketProtocol : public Protocol {
public:
    WebsocketProtocol();
    ~WebsocketProtocol();

    bool Start() override;
    bool SendAudio(std::unique_ptr<AudioStreamPacket> packet) override;
    bool OpenAudioChannel() override;
    void CloseAudioChannel(bool send_goodbye = true) override;
    bool IsAudioChannelOpened() const override;

private:
    EventGroupHandle_t event_group_handle_;
    // WS 常连保活：定时器回调中发心跳或重连
    esp_timer_handle_t keepalive_timer_ = nullptr;
    // 生命周期安全标志（与 MqttProtocol 同款写法）
    std::shared_ptr<std::atomic<bool>> alive_ = std::make_shared<std::atomic<bool>>(true);
    std::unique_ptr<WebSocket> websocket_;
    int version_ = 1;

    // 后台重连静默标志：true 时 SetError 被抑制（对齐 MqttProtocol 的 report_error=false）
    bool suppress_errors_ = false;
    bool OpenAudioChannelQuietly();

    void SendPing();
    void ParseServerHello(const cJSON* root);
    bool SendText(const std::string& text) override;
    std::string GetHelloMessage();
};

#endif
