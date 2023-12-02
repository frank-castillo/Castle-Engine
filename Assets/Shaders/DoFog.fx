cbuffer PerFrameBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
}

cbuffer FogBuffer : register(b1)
{
    float fogStart;
    float fogEnd;
}

Texture2D shaderTexture : register(t0);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD0;
    float fogFactor : FOG;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    float4 cameraPosition;
    
    // Change the position vector to be 4 units for proper matrix caluclations
    input.position.w = 1.0f;
    
    // Calculate the position of the vertex against the worldMatrix, view, and projectionMatrix
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
	
    //Store the texture coordinates for pixel shader
    output.texCoord = input.texCoord;
    
    // We first calculate the Z coordinate of the vertex in view space.
    // We then use that with the fog end and start position in the fog factor equation to produce a fog factor that we send into the pixel shader.
    // Calculate camera positon
    cameraPosition = mul(input.position, worldMatrix);
    cameraPosition = mul(cameraPosition, viewMatrix);
    
    // Calculate the linear fog
    output.fogFactor = saturate((fogEnd - cameraPosition.z) / (fogEnd - fogStart));
    
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 textureColor;
    float4 fogColor;
    float4 finalColor;
    
    // Sample the texture pixel at the current location
    textureColor = shaderTexture.Sample(textureSampler, input.texCoord);
    
    // Set color of fog to grey
    fogColor = float4(0.5f, 0.5f, 0.5f, 1.0f);
    
    // Calculate the final color using the fog effect equation
    // The fog color equation does a linear interpolation between the texture color and the fog color based on the fog factor input value
    finalColor = input.fogFactor * textureColor + (1.0 - input.fogFactor) * fogColor;
    
    return finalColor;
}