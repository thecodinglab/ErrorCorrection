<template>
    <div class="illustration">
      <slot></slot>
    </div>
</template>

<script>
    export default {
        name: "illustration"
    }
</script>

<style lang="scss" scoped>
  @import "../color-palette";
  @import url('https://fonts.googleapis.com/css?family=Roboto+Mono:500');

  .illustration {
    background-color: $dark-gray;
    width: 100%;
    border-radius: 12px;
    padding: 48px;
    margin: 48px 0;
    font-family: 'Roboto Mono', monospace;
  }

</style>
