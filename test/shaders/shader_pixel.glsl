#version 330 core

in vec4 varying_color;
out vec4 gl_FragColor;
uniform vec2 u_p1;
uniform vec2 u_p2;
uniform vec2 u_p3;
uniform vec2 u_position;
uniform vec2 u_resolution;
uniform vec3 u_hue;

vec3 rgb_to_hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv_to_rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 hsl_to_rgb(float h, float s, float l) 
{
    // 1. Calculate the base hue colors using a 6-segment wheel
    vec3 rgb = clamp(abs(mod(h * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0, 0.0, 1.0);
    
    // 2. Adjust for saturation and lightness
    // This formula blends the pure hue with the grayscale based on L and S
    return l + s * (rgb - 0.5) * (1.0 - abs(2.0 * l - 1.0));
}

float rad_to_deg(float rad) 
{
    return rad * 180.0 / 3.14159265;
}

float deg_to_rad(float deg) 
{
    return deg * 3.14159265 / 180.0;
}

vec3 color_wheel(float angle)
{
    return hsv_to_rgb(vec3(angle, 1.0, 1.0));
}

vec2 coordinates(vec2 p, vec2 p1, vec2 p2, vec2 p3)
{
    float dy13 = p3.y - p1.y;
    float dy12 = p2.y - p1.y;
    float dy1 = p.y - p1.y;
    float dx13 = p3.x - p1.x;
    float dx12 = p2.x - p1.x;
    float dx1 = p.x - p1.x;

    float t = (dy13 - dy12)*dx1 - (dx13 - dx12)*dy1;
    float a = dx12*dy13 - dx13*dy12;
    float b = dx12*dy1  - dx1*dy12;

    return vec2(t/a, b/t);
}

vec2 inverseCoordinates(vec2 p1, vec2 p2, vec2 p3, float t1, float t2) 
{
    vec2 dp12 = p2 - p1;
    vec2 dp13 = p3 - p1;
    vec2 p = p1;
    p += dp12 * t1;
    p += (dp13 - dp12) * (t1 * t2);
    return p;
}

void main()
{
    vec4 color = varying_color;
    float innerRadius = 0.8;
    float outerRadius = 1.0;
    float edgeWidth = 0.01; // Smoothness factor
    vec2 fragCoord = gl_FragCoord.xy - u_position;
    vec2 uv = fragCoord.xy / u_resolution.xy;
    vec2 position = uv * 2.0 - 1.0; // Convert to range [-1, 1]
    float angle = atan(position.y, position.x);
    float hue_angle = u_hue.x * 3.14159265 / 180.0;
    float d = length(position);

    if (d > outerRadius) 
    {
           gl_FragColor = varying_color;
           return;
    } 
    else if (d >= innerRadius)
    {   
        float ring = smoothstep(innerRadius - edgeWidth, innerRadius, d) - 
                     smoothstep(outerRadius, outerRadius + edgeWidth, d);

        float a1 = rad_to_deg(angle);
        float a2 = rad_to_deg(hue_angle);

        if (abs(a1 - a2) < 0.5) 
        {
            if (abs(a1 - a2) < 0.25) 
            {
                gl_FragColor = vec4(vec3(1.0), 1.0);
            } 
            else 
            {
                gl_FragColor = vec4(vec3(0.0), 1.0);
            }
        }
        else
        {
            gl_FragColor = vec4(color_wheel(angle / (2.0 * 3.14159265)) * ring, 1.0);
        }
    }
    else
    {
        vec2 t = coordinates(position, u_p1, u_p2, u_p3);

        if (t.x < 0.0 || t.y < 0.0 || t.x > 1.0 || t.y > 1.0) 
        {
           gl_FragColor = varying_color;
           return;
        }       

        // Get the position of the selected saturation and value
        float sat = u_hue.y;
        float val = u_hue.z;
        vec2 indicatorPos = inverseCoordinates(u_p1, u_p2, u_p3, val, sat);

        // Calculate distance from current fragment to indicator position
        float distToIndicator = length(position - indicatorPos);

        // Draw black circle at the indicator position
        float circleInnerRadius = 0.035;
        float circleOuterRadius = 0.05;

        if (distToIndicator < circleOuterRadius) 
        {
            if (distToIndicator >= circleInnerRadius) 
            {
                gl_FragColor = vec4(1.0);
                return;
            }
        }

        vec3 hsv = vec3(hue_angle / (2.0 * 3.14159265), t.y, t.x);
        vec3 rgb = hsv_to_rgb(hsv);

        gl_FragColor = vec4(rgb, 1.0);
    }
}
