#version 460 core

// primitive we are receiving 
layout (points) in;

// primitive we are producing, along with max number of vertices. Extra vertices won't get drawn
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

// transform points into triangle strips
void build_house(vec4 position)
{    
    fColor = gs_in[0].color;

    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:bottom-left
    EmitVertex();       // "go to next vertex"
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:top
    fColor = vec3(1.0, 1.0, 1.0);       // change color of last vertex
    EmitVertex();
    EndPrimitive();     // "end drawing"
}



void main()
{
    // gl_in: glsl variable for geom shader input
    build_house(gl_in[0].gl_Position);
}


