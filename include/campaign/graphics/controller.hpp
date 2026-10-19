#ifndef CAMPAIGN_GRAPHICS_CONTROLLER_HPP
#define CAMPAIGN_GRAPHICS_CONTROLLER_HPP
namespace CampaignGraphics {
struct ControllerBase { virtual void Release(); };
// Partial PS2 view. Class identity and the intervening fields remain unknown.
struct Controller : ControllerBase {
    unsigned char unknown04[0xe4];
    unsigned int backend;
    unsigned int port;
    bool Open(unsigned int backendHandle, unsigned int portIndex);
};
typedef char Controller_backend_offset[((int)&((Controller*)0)->backend == 0xe8) ? 1 : -1];
typedef char Controller_port_offset[((int)&((Controller*)0)->port == 0xec) ? 1 : -1];
}
#endif
