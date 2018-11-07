import Vue from 'vue'
import App from './App.vue'

import Router from 'vue-router'
Vue.use(Router)

import Visualization from "./pages/Visualization"

const router = new Router({
  mode: 'history',
  routes: [
    {path: '/', name: 'home', component: Visualization},
  ]
})

new Vue({
  router,
  el: '#app',
  render: h => h(App)
})
