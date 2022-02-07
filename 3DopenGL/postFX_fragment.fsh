#version 440
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

uint wanghash( uint seed )
{
    seed = (seed ^ 61u) ^ (seed >> 16);
    seed *= 9u;
    seed = seed ^ (seed >> 4);
    seed *= 0x27d4eb2du;
    seed = seed ^ (seed >> 15);
    return seed;
}

vec4 unmodified()
{
    return texture2D(screenTexture, TexCoords).xyzw;
}

vec4 circle()
{
    float du = TexCoords.x - 0.5f, dv = TexCoords.y - 0.5f;
    float dist = sqrt( du * du + dv * dv );
    if (dist < 0.5f && dist > 0.45f) return vec4 ( 1.0f, 0.0f, 0.0f, 1.0f ); else return unmodified();
}

vec4 vignetting()
{
    float du = TexCoords.x - 0.5, dv = TexCoords.y - 0.5;
    float dist = sqrt ( du * du + dv * dv );
    float intensity = cos ( dist * 2.0 );
    return unmodified() * intensity;
}

vec4 aberration()
{
    float du = TexCoords.x - 0.5, dv = TexCoords.y - 0.5;
    float dist = sqrt ( du * du + dv * dv );
    float red = texture2D( screenTexture, TexCoords * (1.0 + dist / 40.0) ).x;
    float green = texture2D( screenTexture, TexCoords ).y;
    float blue = texture2D( screenTexture, TexCoords * (1.0 - dist / 40.0) ).z;
    return vec4( red, green, blue, 1);

}

vec4 grain()
{
    uvec2 iuv = uvec2 ( uint ( TexCoords.x * 2048.0 ), uint( TexCoords.y * 2048.0 ) );
    uint pixelIdx = iuv.x + 2048u * iuv.y;
    uint seed = wanghash(pixelIdx * 65129u); //prime
    //seed ^= seed << 13;
    //seed ^= seed >> 7;
    //seed ^= seed << 17;
    float intensity = 0.75 + 0.5 * (float( seed >> 24 ) / 256.0 );
    return unmodified() * intensity;
}

void main()
{ 
    FragColor = unmodified();
    //FragColor = circle();
    //FragColor = vignetting();
    //FragColor = aberration();
    //FragColor = grain() + aberration();
    //FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}