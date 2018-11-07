<template>
  <illustration>
    <div v-for="(row, i) in rows" class="flex row">
      <p v-html="getIndents(row.indents)"></p>
      <div>
        <p v-if="i === 0">{{ row.data }}<span class="append">{{ appending }}</span></p>
        <p v-else>{{ row.data }}<span class="append">{{ row.append }}</span></p>
        <div class="flex">
          <p v-html="getIndents(row.indent)"></p>
          <p class="polynomial">{{ polynomial }}</p>
        </div>
      </div>
    </div>
    <div class="flex row">
      <p v-html="getIndents(indents)"></p>
      <p><span class="append">{{ result.prepend }}</span>{{ result.data }}</p>
    </div>
  </illustration>
</template>

<script>
  import Illustration from "../layouts/illustration";

  export default {
    name: "crc-illustration",
    components: {Illustration},
    props: ['bits'],
    data() {
      return {
        polynomial: '100011101',
        solution: ''
      }
    },
    computed: {
      rows() {
        const rows = [];
        const polynomial = this.polynomial;

        let data = '10011001'; // TODO: Set to this.bits
        let indents = 0;
        let length = data.length + polynomial.length - 1;

        while (true) {
          const indent = data.indexOf('1');

          let append = '';
          for (let i = 0; i < polynomial.length - (data.length - indent); i++) {
            append += '0';
          }

          rows.push({data, append, indent, indents});
          indents += indent;

          // XOR
          const normalized = data.substring(indent) + append;
          data = '';
          for (let i = 0; i < polynomial.length; i++) {
            data += parseInt(polynomial.charAt(i)) ^ parseInt(normalized.charAt(i));
          }

          if (indents + polynomial.length >= length) {
            this.solution = data;
            break;
          }
        }

        return rows;
      },
      indents() {
        const row = this.rows[this.rows.length-1];
        return row.indents + row.indent;
      },
      result() {
        const p = this.solution.length - (this.polynomial.length - 1);
        let prepend = '';
        for (let i = 0; i < p; i++) prepend += '0'
        return {
          data: this.solution.substring(p),
          prepend
        }
      },
      appending() {
        let append = '';
        for (let i = 0; i < this.polynomial.length - 1; i++) {
          append += '0';
        }
        return append;
      }
    },
    methods: {
      getIndents(range) {
        let indents = '';
        for (let i = 0; i < range; i++) {
          indents += '&nbsp;';
        }
        return indents;
      }
    }
  }
</script>

<style lang="scss" scoped>
  @import "../color-palette";

  .row {
    p {
      margin: 0;
      letter-spacing: 2px;
    }

    .data {

    }

    .polynomial {
      color: $blue;
      border-bottom: 2px solid $light-gray;
      width: max-content;
    }

  }

  .append {
    color: $light-gray;
  }

  .flex {
    display: flex;
  }

</style>
