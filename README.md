demo-scene
==========

Playing around with creating size restricted graphics demos.

Al C programs are compiled with Pelles C IDE which you can acquire
here: http://www.smorgasbordet.com/pellesc/

You don't anything but an OpenGL 2 capable GPU that supports Shader Model 2.0.
RAM requirements are high due to Crinkler decompression at run-time which requires
about 100MB unless otherwise stated below.

Fractals
=======
This branch of my demoscene repo contains some fractal demos I have created.
As of 14/05/2012 the contents of this branch are:
 * Mandelbrot set in 2D (984 bytes)
 * Julia set in 2D(988 bytes)

Fractals have long fascinated me, but for some reason I thought they would
be difficult to implement.  The following example programs prove how wrong
I was!  Over time I aim to be creating some 3D fractals in less than 4K; this
may prove over ambitious, but I'm still learning about what is possible and
what is not in the intro/demo-scene.
 
Mandelbrot Set
==============
The mandelbrot was the first demo in this branch.  It is written in C99 using
only the Windows API and a few OpenGL extensions plus GLSL.  Crinkler was used
to compress the final exe down to size. 

As it is my firtst demo it isn't remarkable, but it is nonetheless a step in the
right direction.  I toyed with animating the fractal, but alas could not keep it
within the size constrained of 1k; it is therefore static.  Texturing was also
difficult due to size constraints.  I could not succeed in generating an interesting
texture in 1k to add some exciting colours to my fractal - yet!  My intention is to
return to this later and apply everything I have learned since in order to make this
intro what it can really be - a beautiful rendering of an amasing phenomenon.

Julia Set
=========
Since everyone talks about Julia and Mandelbrot sets together, I decided to go with
the flow and create a Julia set too.  I toyed with the idea of combining this fractal
with the above Mandelbrot set but, again, I am not yet skilled enough in size coding
to achieve this.  The program is again written in C99 with the Win32 API, OpenGL
and GLSL.

Again, since this is my first foray into fractals and intros, it isn't all that
remarkable when compared to other efforts out there, but in time I aim to fix this
up and add more excitement to the intro.