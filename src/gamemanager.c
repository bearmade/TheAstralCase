#include <../inc/gamemanager.h>
#include <resources.h>
#include <genesis.h>

void showSegaLogo() {
    // Load the logo image and palette
    PAL_setPalette(PAL2, segaLogo.palette->data, DMA);
    VDP_drawImageEx(BG_B, &segaLogo, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, 0), 0, 0, FALSE, TRUE);
    
    // Create an array to hold the scroll offsets for each line
    s16 scrollOffsets[224];
    
    // Initialize all lines to be off-screen (to the right)
    for (int i = 0; i < 224; i++) {
        scrollOffsets[i] = 256; // Start off-screen
    }
    
    // Apply initial scroll position
    VDP_setHorizontalScrollLine(BG_B, 0, scrollOffsets, 224, DMA);
    
    // Play the Sega sound
    //XGM_setPCM(SFX_SEGA, sfx_sega, sizeof(sfx_sega));
    //XGM_startPlayPCM(SFX_SEGA, 15, SOUND_PCM_CH2);
    
    // Cascade effect: gradually move each line into place
    for (int frame = 0; frame < 120; frame++) { // 120 frames for the animation
        // Update scrollOffsets based on current frame
        for (int line = 0; line < 224; line++) {
            // Create a delay effect where each line starts moving at a different time
            int lineDelay = line / 2; // Adjust this divisor to control cascade speed
            
            if (frame >= lineDelay) {
                // Calculate new position for this line
                int progress = frame - lineDelay;
                if (progress < 40) { // 40 frames for each line to move into place
                    scrollOffsets[line] = 256 - (progress * 16); // Gradually move from right to left
                } else {
                    scrollOffsets[line] = 0; // Final position
                }
            }
        }
        
        // Apply the updated scrolling
        VDP_setHorizontalScrollLine(BG_B, 0, scrollOffsets, 224, DMA);
        
        // Wait for next frame
        SYS_doVBlankProcess();
    }
    
    // Reset scrolling after the animation is complete
    VDP_setHorizontalScrollLine(BG_B, 0, NULL, 0, CPU);
    
    // Wait for the specified time
    waitMs(240); 
    PAL_fadeOut(0, 63, 60, 1);
}
