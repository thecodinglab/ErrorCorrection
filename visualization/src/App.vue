<template>
  <div id="app">
    <router-view></router-view>
  </div>
</template>

<script>
  export default {
    name: 'app',
    data() {
      return {}
    }
  }
</script>

<style lang="scss">
  @import "color-palette";
  @import url('https://fonts.googleapis.com/css?family=Roboto:400,500');

  * {
    padding: 0;
    margin: 0;
    box-sizing: border-box;
  }

  #app {
    font-family: 'Roboto', Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    background-color: $background-gray;
    min-height: 100vh;
    color: white;
  }

  h2 {
    font-size: 32px;
    font-weight: 500;
    margin-bottom: 8px;
  }

  h3 {
    font-size: 24px;
    font-weight: 500;
    margin-bottom: 8px;
  }

  p {
    font-size: 16px;
    font-weight: 400;
    margin-bottom: 8px;
  }

  a {
    color: $blue;
  }

  .blue {
    color: $blue;
  }

  .content-wrapper {
    max-width: 1200px;
    margin: auto;
    padding: 48px;
  }

</style>
