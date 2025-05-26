/* primitives.c ... */

/*
 * This example creates an SDL window and renderer, and then draws some lines,
 * rectangles and points to it every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include "../cpu/Disassembler.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cstdio>
#include <cstdlib>
#include <error.h>
#include <fcntl.h>
#include <format>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_FPoint points[500];
static Uint64 lastTime;
static char *program;
static CPU *cpu;
int callGraphFD;
int highMemFD;
int instructionsFD;
int serialFD;
int memFD;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    int i;
    callGraphFD = open("/home/simon/dev/gemu/callGraph.txt",
                       O_WRONLY | O_CREAT | O_TRUNC, 0666);
    highMemFD = open("/home/simon/dev/gemu/highMemWrites.txt",
                     O_WRONLY | O_CREAT | O_TRUNC, 0666);
    memFD = open("/home/simon/dev/gemu/memWrites.txt",
                 O_WRONLY | O_CREAT | O_TRUNC, 0666);
    instructionsFD = open("/home/simon/dev/gemu/instructions.txt",
                          O_WRONLY | O_CREAT | O_TRUNC, 0666);
    serialFD = open("/home/simon/dev/gemu/serial.txt",
                    O_WRONLY | O_CREAT | O_TRUNC, 0666);

    SDL_SetAppMetadata("Example Renderer Primitives", "1.0",
                       "com.example.renderer-primitives");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/primitives", 640, 480,
                                     0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* set up some random points */
    for (i = 0; i < SDL_arraysize(points); i++) {
        points[i].x = (SDL_randf() * 440.0f) + 100.0f;
        points[i].y = (SDL_randf() * 280.0f) + 100.0f;
    }
    lastTime = SDL_GetTicks();

    // int fd = open("./Pokemon Red (UE) [S][!].gb", O_RDONLY, 0600);
    int fd = open(argv[1], O_RDONLY, 0600);
    if (fd == -1) {
        perror("Error opening game file");
        exit(EXIT_FAILURE);
    }
    struct stat st;
    stat(argv[1], &st);
    long size = st.st_size;
    printf("size of program is 0x%lx", size);
    program = (char *)mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (program == MAP_FAILED) {
        perror("Error mapping game file");
        exit(EXIT_FAILURE);
    }
    std::cout << "Program pointer " << std::hex << (long)program << "\n";
    cpu = new CPU(program);
    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS.
                                 */
    }
    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
    SDL_FRect rect;
    Uint64 currentTime = SDL_GetTicks();

    printf("starting to iterate\n");
    int currentFrame = 0;
    while (currentFrame < CYCLES_PER_FRAME) {
        cpu->tick();
        currentFrame += 1;
    }
    printf("should have printed frame\n");
    /* as you can see from this, rendering draws over whatever was drawn before
     * it. */

    SDL_SetRenderDrawColor(renderer, 33, 33, 33,
                           SDL_ALPHA_OPAQUE); /* dark gray, full alpha */
    SDL_RenderClear(renderer);                /* start with a blank canvas. */

    /* draw a filled rectangle in the middle of the canvas. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 255,
                           SDL_ALPHA_OPAQUE); /* blue, full alpha */
    rect.x = rect.y = 100;
    rect.w = 440;
    rect.h = 280;
    SDL_RenderFillRect(renderer, &rect);

    /* draw some points across the canvas. */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0,
                           SDL_ALPHA_OPAQUE); /* red, full alpha */
    SDL_RenderPoints(renderer, points, SDL_arraysize(points));

    SDL_RenderDebugText(renderer, 0, 90,
                        std::format("Ticks: {}", currentTime).c_str());

    /* draw a unfilled rectangle in-set a little bit. */
    SDL_SetRenderDrawColor(renderer, 0, 255, 0,
                           SDL_ALPHA_OPAQUE); /* green, full alpha */
    rect.x += 30;
    rect.y += 30;
    rect.w -= 60;
    rect.h -= 60;
    SDL_RenderRect(renderer, &rect);

    /* draw two lines in an X across the whole canvas. */
    SDL_SetRenderDrawColor(renderer, 255, 255, 0,
                           SDL_ALPHA_OPAQUE); /* yellow, full alpha */
    SDL_RenderLine(renderer, 0, 0, 640, 480);
    SDL_RenderLine(renderer, 0, 480, 640, 0);

    Uint64 afterTime = SDL_GetTicks();
    SDL_RenderDebugText(
        renderer, 0, 100,
        std::format("Frames: {}", 1000 / (16 - (afterTime - currentTime)))
            .c_str());
    SDL_RenderPresent(renderer); /* put it all on the screen! */

    printf("before delay with aftertime %lu and currentTime %lu\n", afterTime,
           currentTime);
    if (afterTime - currentTime < 16) {
        //SDL_Delay(16 - (afterTime - currentTime));
    }

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    /* SDL will clean up the window/renderer for us. */
}
