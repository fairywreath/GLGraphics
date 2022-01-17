#version 460 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

vec4 invertColor();
vec4 grayscale();
vec4 sharpenKernel();
vec4 blur();
vec4 edgeDetection();

// 3x3 kernel 
vec4 kernelEffect(float offset, float kernel[9]);

void main()
{ 
    FragColor = texture(screenTexture, TexCoords);
//	FragColor = vec4(1, 0, 0, 0);
    
    /* post processing */
//    FragColor = invertColor();
//    FragColor = grayscale();
//    FragColor = sharpenKernel();
//    FragColor = blur();
//    FragColor = edgeDetection();
}

vec4 invertColor() {
    return vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0); 
}

vec4 grayscale() {
    vec4 color = texture(screenTexture, TexCoords);
    float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    return vec4(average, average, average, 1.0);
}

vec4 sharpenKernel() {
    const float offset = 1.0 / 300.0;  
       
    // kernel matrix
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    
    return kernelEffect(offset, kernel);
}

vec4 blur() {
    const float offset = 1.0 / 300.0; 

    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    return kernelEffect(offset, kernel);
}


vec4 edgeDetection() {
    const float offset = 1.0 / 300.0; 

    float kernel[9] = float[](
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    );

    return kernelEffect(offset, kernel);
}

vec4 kernelEffect(float offset, float kernel[9]) {
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    
    // get texcoords from surroundings(3 x 3)
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];


    return vec4(col, 1.0);
}