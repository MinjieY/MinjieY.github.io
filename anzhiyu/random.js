var posts=["post/4960c6d9.html","post/deab04e1.html","post/1e432c02.html","post/0.html","post/7c8327f0.html","post/c3f5278c.html","post/15f4d9b2.html","post/15f4d9b2.html"];function toRandomPost(){
    pjax.loadUrl('/'+posts[Math.floor(Math.random() * posts.length)]);
  };