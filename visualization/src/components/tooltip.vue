<template>
  <div class="tooltip">
    <slot></slot>
    <span class="text">{{ tooltip }}</span>
  </div>
</template>

<script>
  export default {
    name: "tooltip",
    props: ['tooltip']
  }
</script>

<style lang="scss" scoped>
  @import "../color-palette";

  @keyframes fade {
    from {

    }
    to {

    }
  }

  .tooltip {
    position: relative;
    display: inline-block;
    cursor: pointer;
    transition: background-color 0.2s;

    .text {
      opacity: 0;
      width: 120px;
      background-color: rgba(darken($dark-gray, 5%), 0.9);
      color: #fff;
      text-align: center;
      padding: 5px 0;
      border-radius: 6px;
      font-family: 'Roboto', Helvetica, Arial, sans-serif;
      transition: opacity 0.2s;

      /* Position the tooltip text - see examples below! */
      position: absolute;
      z-index: 1;
      top: 120%;
      left: 50%;
      margin-left: -60px;
    }

    &:hover {
      background-color: darken($dark-gray, 5%);

      .text {
        opacity: 1;
        visibility: visible;
      }
    }
  }
</style>
