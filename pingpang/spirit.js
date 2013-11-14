
Star = {

  initialize: function(width) {
    this.speed = 40;
    this.x = Game.random(0,width);
    this.y = 0;
    this.color = "#FFFFFF";
    this.width = 2;
    this.height = 2;
  }
};

Ship = {
    initialize : function(workspace){
        this.imageSrc = "./images/sb_ship.gif";
        this.image = workspace.images[this.imageSrc];
        this.fireImgSrc = ["./images/sb_fire0.gif",
                           "./images/sb_fire1.gif"];
        this.fireImgs = new Array();
        for(var i = 0;i< this.fireImgSrc.length; ++i)
            this.fireImgs.push(workspace.images[this.fireImgSrc[i]]);
        this.width = this.image.width;
        this.height = this.image.height;
        this.x = workspace.width/2-this.width/2;
        this.y = workspace.height-this.height;
        this.topWidth = workspace.width;
        this.topHeight = workspace.height;
        this.index = 0;
        this.count = 0;
        this.blood = 100;
    },

    draw : function(ctx){
      ctx.drawImage(this.image,this.x,this.y);
      ctx.drawImage(this.fireImgs[this.index],this.x+this.width/2-6,this.y+this.height);
      if(++this.count === 20) this.count = 0;
      if(this.count < 10) this.index = 0;
      else this.index = 1;
    },

    moveLeft : function(step){
        this.x = this.x - step;
        if(this.x < 0)
            this.x = 0;
    },

    moveRight : function(step){
        this.x += step;
        if(this.x + this.width > this.topWidth)
            this.x = this.topWidth - this.width;
    },

    moveUp : function(step){
        this.y -= step;
        if(this.y < 0)
            this.y = 0;
    },

    moveDown : function(step){
        this.y += step;
        if(this.y + this.height > this.topHeight)
            this.y = this.topHeight - this.height;
    },
};

Bullet = {
    initialize : function(workspace){
        this.imageSrc = "./images/sb_bullet.gif";
        this.image = workspace.images[this.imageSrc];
        this.width = this.image.width;
        this.height = this.image.height;
        this.x = 0;
        this.y = 0;
        this.speed = 100;
        this.isDisposed = false;
    },

    draw : function(ctx){
        if(this.isDisposed == false)
            ctx.drawImage(this.image,this.x,this.y);
    },
};

Meteor = {
    initialize : function(workspace){
        this.imageSrc = ["./images/sb_meteor.gif",
                         "./images/sb_boom0.gif",
                         "./images/sb_boom1.gif",
                         "./images/sb_boom2.gif",
                         "./images/sb_boom3.gif",
                         "./images/sb_boom4.gif"];
        this.image = new Array();
        for(var i = 0;i< this.imageSrc.length; ++i)
            this.image.push(workspace.images[this.imageSrc[i]]);
        this.width = this.image[0].width;
        this.height = this.image[0].height;
        this.x = Game.random(0,workspace.width-this.width);
        this.y = -this.height;
        this.speed = 60;
        this.status = 0;   // 0:live 1-5:dispearing 6:disposed
    },

    draw : function(ctx){
        if(this.status < 6)
            ctx.drawImage(this.image[this.status],this.x,this.y);
        if(this.status > 0 && this.status < 6) this.status++;
    }
};
