Workspace = {

  Defaults: {
    width:  480,   // logical canvas width (browser will scale to physical canvas size - which is controlled by @media css queries)
    height: 640,   // logical canvas height (ditto)
    stats: true,   // tell Game.Runner to show stats
  },

  Images : ["./images/sb_ship.gif",
            "./images/sb_bullet.gif",
            "./images/sb_meteor.gif",
            "./images/sb_boom0.gif",
            "./images/sb_boom1.gif",
            "./images/sb_boom2.gif",
            "./images/sb_boom3.gif",
            "./images/sb_boom4.gif",
            "./images/sb_fire0.gif",
            "./images/sb_fire1.gif"],

  //-----------------------------------------------------------------------------

  initialize: function(runner, cfg) {
    Game.loadImages(this.Images, function(images) {
    this.cfg         = cfg;
    this.runner      = runner;
    this.width       = runner.width;
    this.height      = runner.height;
    this.time        = 0;
    this.runner.start();
    this.stars = new Array();
    this.count1 = 0;
    this.starDuration = 60;
    this.images = images;
    this.ship = Object.construct(Ship,this);
    this.bullets = new Array();
    this.meteors = new Array();
    this.count2 = 0;
    this.meteorDuration = 200;
    }.bind(this));
  },

  update: function(dt) {
    this.time = this.time + dt;
    // stars
    for(var i = 0; i<this.stars.length ;i++){
         this.stars[i].y = this.stars[i].y + this.stars[i].speed*dt;
    }
    if(this.count1 === 0){
        this.stars.push(Object.construct(Star,this.width));
    }
    if(this.stars[0].y > this.height)
        this.stars.shift();
    this.count1++;
    if(this.count1 === this.starDuration) this.count1 = 0;
    //bullets
    for(var i=0; i<this.bullets.length;i++){
        this.bullets[i].y -= this.bullets[i].speed*dt;
    }
    if(this.bullets.length > 0 && this.bullets[0].y < 0)
        this.bullets.shift();
    //meteors
    for(var i = 0;i < this.meteors.length ; i++)
        this.meteors[i].y += this.meteors[i].speed*dt;
    if(this.count2 === 0)
        this.meteors.push(Object.construct(Meteor,this));
    if(this.meteors.length > 0 && this.meteors[0].y > this.height)
        this.meteors.shift();
    this.count2++;
    if(this.count2 === this.meteorDuration) this.count2 = 0;
    // check for collision
    this.checkForCollision();
  },

  draw: function(ctx) {
      //background
      ctx.fillStyle="#000000";
      ctx.fillRect(0,0,this.width,this.height);
      //stars
      for(var i = 0; i<this.stars.length ;i++){
          ctx.fillStyle=this.stars[i].color;
          ctx.fillRect(this.stars[i].x,this.stars[i].y,this.stars[i].width,this.stars[i].height);
      }
      //ship
      this.ship.draw(ctx);
      //bullets
      for(var i = 0;i<this.bullets.length;i++)
          this.bullets[i].draw(ctx);
      //meteors
      for(var i = 0;i<this.meteors.length;i++)
          this.meteors[i].draw(ctx);
  },

  checkForCollision : function(){
      // bullet and meteor
      for(var i = this.bullets.length-1;i>=0;i--){
          if(this.bullets[i].isDisposed === false){
              for(var j = 0;j<this.meteors.length;j++)
                if(this.meteors[j].status == 0 && this.intersection(this.bullets[i],this.meteors[j])){
                    this.bullets[i].isDisposed = true;
                    this.meteors[j].status = 1;
                    break;
                }
          }
      }
      // ship and meteor
      for(var j = 0; j < this.meteors.length;++j)
        if(this.meteors[j].status == 0 && this.intersection(this.ship,this.meteors[j])){
            this.meteors[j].status = 1;
            this.ship.blood -= 20;
            break;
        }
  },

  intersection : function(rect1,rect2){
      if(rect1.x+rect1.width < rect2.x) return false;
      if(rect1.x > rect2.x + rect2.width) return false;
      if(rect1.y > rect2.y + rect2.height) return false;
      if(rect1.y + rect1.height < rect2.y) return false;
      return true;
  },

  onkeydown : function(keyCode){
      switch(keyCode){
          case Game.KEY.LEFT : this.ship.moveLeft(5);break;
          case Game.KEY.RIGHT : this.ship.moveRight(5);break;
          case Game.KEY.UP : this.ship.moveUp(5);break;
          case Game.KEY.DOWN : this.ship.moveDown(5);break;
          case Game.KEY.SPACE :
              var oneBullet = Object.construct(Bullet,this);
              oneBullet.x = this.ship.x + this.ship.width/2 - oneBullet.width/2;
              oneBullet.y = this.ship.y;
              this.bullets.push(oneBullet);
              break;
      }
  },
}; // Workspace.
