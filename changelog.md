Version: 01-12-2024_1 Alpha
Changes:
- Unicode text renderer. 

--------------------------------------------------------------------------------------


Version: 11-11-2024_1 Alpha
Changes:
- Rewrote renderer to use bgfx. 
- cant remember the rest. 

--------------------------------------------------------------------------------------

Version: 02-09-2024_1 Alpha
Changes:
- Initial renderer refactor. 

--------------------------------------------------------------------------------------

Version: 28-08-2024_1 Alpha
Changes:
- Added GameNetworkignSocket(can be disabled). 
- Fixed crash when there is no camera.

--------------------------------------------------------------------------------------

Version: 26-08-2024_1 Alpha
Changes:
- Some dependencies are now submodules. 

--------------------------------------------------------------------------------------

Version: 25-08-2024_4 Alpha
Changes:
- Headless mode

--------------------------------------------------------------------------------------

Version: 25-08-2024_3 Alpha
Changes:
- Added idiot proofed transform component 

--------------------------------------------------------------------------------------

Version: 25-08-2024_2 Alpha
Changes:
- Added 
    - GetKeyDown(only return true if key pressed and holding it will return false)
    - GetKeyUp(only return true if key released)
    - GetKey(return true if key is pressed no matter what)
    - GetMouseButtonDown(same as key but for mouse button)
    - GetMouseButtonUp(same as key but for mouse button)
    - GetMouseButton(same as key but for mouse button)

--------------------------------------------------------------------------------------

Version: 25-08-2024_1 Alpha
Changes:
- Fixed extremely large quantity of typos in AudioEngine and AudioSource. Also fixed audio not coming through right direction.
- Some transform related issue fix

--------------------------------------------------------------------------------------

Version: 22-08-2024_1 Alpha
Changes:
- Multithreading in some World systems.
- Fixed most warnings.
- Fixed audio engine not working on release builds (specifically, when asserts are disabled)

--------------------------------------------------------------------------------------

Version: 19-08-2024_1 Alpha
Changes:
- Created console. 
- Application settings can be set at startup using tbconfig file. 
- Added a way to switch between fullscreen modes in Window.

--------------------------------------------------------------------------------------

Version: 18-08-2024_1 Alpha
Changes:
- Fixed GLTFloader oversight. 
- Application is now a proper singleton. 
- Instead of Config.h, now every config is in ApplicationSpecification
- Framebuffer fix and clean up. 
- Further tracy coverage
- Cleaned up some code.

--------------------------------------------------------------------------------------

Version: 17-08-2024_1 Alpha
Changes:
- Font is now visible on opengl es 3.0. 
- GPU profiling (not supported for GLES 3). And expanded tracy profiler coverage. I believe all Functions are covered. 
- FrameImage now visible in tracy
- "Cleaned" some code

--------------------------------------------------------------------------------------

Version: 15-08-2024_1 Alpha
Changes:
- Done changes to naming, presolve and collision callbacks. 
- Integrated Font to asset manager.
- Integrated Audio(formerly known as Music) to asset manager.
- Asset manager is now a proper singleton.
- Fixed crash when program was closing which was caused by Audio Engine oversight.
- Initial work for audio to properly handle streamin (basically compatible with assetpacks whenever it will be added to engine)
- Removed libsndfile to preseve my sanity (no mp3 or any other sound format support for a looong time :3)
- Added AudioSourceComponent (Note: openal does falloff only to mono audios)
- Added AudioListenerComponent
- Now audio source is PROPERLY streaming music from file.

--------------------------------------------------------------------------------------

Version: 09-08-2024_1 Alpha
Changes:
- Added resources. It holds structs and there can be one of same type at a time. 
- Made World::Init() function private and now you have to just run World::OnStart().
- Added way to set gravity after initialization of Physics2D.
- Nuked NativeSctiptComponent out of existence.
- Added way to set body touch event callback and presolve function in Rigidbody2DComponent. 

--------------------------------------------------------------------------------------

Version: 08-08-2024_1 Alpha
Changes:
- Added mouse delta to Input. 
- Added ability to pring vectors matrices and quaternions. 

--------------------------------------------------------------------------------------

Version: 06-08-2024_3 Alpha
Changes:
- Removed Plugin. 

--------------------------------------------------------------------------------------

Version: 06-08-2024_2 Alpha
Changes:
- GLTFLoader is now just a buncha functions. 

--------------------------------------------------------------------------------------

Version: 06-08-2024_2 Alpha
Changes:
- Fixed GLTFLoader not loading texture correctly from .glb files.

--------------------------------------------------------------------------------------

Version: 06-08-2024_1 Alpha
Changes:
- Updated box2d which fixed body stopping to move after velocity becomes 0
- Made so transform position changes rigidbody position 
- Updated GLTF loader and moved to assets since its not really related to rendering
- Removed timestep.
- Removed prefab.
- Removed scriptable entity.
- Created  
    - IntVector2 
    - IntVector3 
    - IntVector4 
    - UIntVector2
    - UIntVector3
    - UIntVector4
    - Vector2    
    - Vector3    
    - Vector4    
    - Matrix2    
    - Matrix3    
    - Matrix4    
    - Quaternion 
        - Which are alias of glm types


--------------------------------------------------------------------------------------

Version: 26-07-2024_1 Alpha
Changes:
- Created Random class.
- Subdata editing for vertex buffer.

--------------------------------------------------------------------------------------

Version: 22-07-2024_1 Alpha
Changes:
- OpenGL 4.6 support.

--------------------------------------------------------------------------------------

Version: 20-07-2024_5 Alpha
Changes:
- Print error when window initialization fails.

--------------------------------------------------------------------------------------

Version: 20-07-2024_4 Alpha
Changes:
- Fixed typos.

--------------------------------------------------------------------------------------

Version: 20-07-2024_3 Alpha
Changes:
- Added resizeable, vsync minwidth and minheight flag to application specs.
- By default working directory is in assets folder.

--------------------------------------------------------------------------------------

Version: 20-07-2024_2 Alpha
Changes:
- Moved examples to different repo.  

--------------------------------------------------------------------------------------

Version: 20-07-2024_1 Alpha
Changes:
- "Fixed" an oversight.  

--------------------------------------------------------------------------------------

Version: 19-07-2024_1 Alpha
Changes:
- "Fixed" OpenGL 3.0 ES Framebuffer. i'll clean it up later.  
- Tried to fix web builds. Framebuffer is broken specifically on web builds and no mesh/quad is visible.

--------------------------------------------------------------------------------------

Version: 06-07-2024_3 Alpha
Changes:
- Removed FileSystemData  

--------------------------------------------------------------------------------------

Version: 06-07-2024_2 Alpha
Changes:
- Fixed oversight where working directory in FileSystem did not get updated  

--------------------------------------------------------------------------------------

Version: 06-07-2024_1 Alpha
Changes:
- Removed ImGui Panels from engine code 

--------------------------------------------------------------------------------------

Version: 02-07-2024_1 Alpha
Changes:
- File dialog support for linux 
    - Using gtk4 to create file dialog
- Removed level-editor. Instead a new project has started to create 2D level/map standard.

--------------------------------------------------------------------------------------

Version: 20-06-2024_1 Alpha
Changes:
- Bevy like system thingy idk check World.h/cpp
    - Instead of NativeSctiptComponent now u create components and systems like in bevy. Prefab need a bit of work to fully work.

--------------------------------------------------------------------------------------

Version: 15-06-2024_1 Alpha
Changes:
- Further mesh/gltf work and bug fix.
- Framebuffer temp bug fix.
    - Now has working depth buffer

--------------------------------------------------------------------------------------

Version: 14-06-2024_1 Alpha
Changes:
- Initial mesh/gltf work. 

--------------------------------------------------------------------------------------

Version: 25-05-2024_2 Alpha
Changes:
- Fixed infinite recusion when instantiating prefab that had root entity with a child. 

--------------------------------------------------------------------------------------

Version: 25-05-2024_1 Alpha
Changes:
- Added Prefab class which serializes in to Tabby Prefab Format (tbpf)

