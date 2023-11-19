<template>
  <!-- 定义该组件的模板 -->
  <div id="app">
    <img src="./assets/logo.png">
      <div>
        <el-button @click="StartNotify">element-ui 安装成功</el-button>
      </div>
      <!-- 导航条 -->
      <hr>
      <UserInfo></UserInfo>
  </div>
</template>

<script>
  // import xx from 'yy'
  import UserInfo from './UserInfo.vue'
  
  // export 导出一个成员，然后可以被其它模块import
  // export default 导出一个默认成员
  // 一个模块只能有一个默认成员，其它模块可以使用任意名称导入这成员
  export default {
    name: 'app',
    data () {
      // 用return返回一个新对象，避免多个模块引入同一个对象
      // 调用者用data()函数获得一个新对象
      return {
        msg: 'Welcome to Your Vue.js App'
      }
    },
    // 定义组件方法
    methods: {
      StartNotify() {
        // 发送一个vue通知
        this.$notify({
          title: 'It works!',
          type: 'success',
          message: 'We\'ve laid the ground work for you. It\'s time for you to build something epic!',
          duration: 5000
        })
      }
    },
    components: {
      // 定义该组件用到的其它组件
      UserInfo
  	}
  }
</script>

<style>
  #app {
    font-family: 'Avenir', Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    color: #2c3e50;
    margin-top: 60px;
  }

  h1, h2 {
    font-weight: normal;
  }

  ul {
    list-style-type: none;
    padding: 0;
  }

  li {
    display: inline-block;
    margin: 0 10px;
  }

  a {
    color: #42b983;
  }
</style>