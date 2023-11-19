import Vue from 'vue'
// export default 导出的对象App
import App from './App.vue'

import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';

Vue.use(ElementUI);

import axios from 'axios';
Vue.prototype.$axios = axios

// import moment  from 'moment'

new Vue({
  el: '#app',
  /*
  render是一个渲染函数
  createElement是一个创建节点的函数
  App就是一个html根文件

  render: function(createElement) {
    return createElement(App)
  }
  */
  render: h => h(App),
})
