<template>
  <illustration>
    <div v-for="(row, i) in rows" class="flex row">
      <p v-html="getIndents(row.indents)" class="indent"></p>
      <div>
        <p>{{ row.data }}<span class="append">{{ row.append }}</span></p>
        <div class="flex">
          <p v-html="getIndents(row.indent)"></p>
          <p class="polynomial">{{ polynomial }}</p>
        </div>
      </div>
    </div>
    <div class="flex">
      <p v-html="getIndents(indents)" class="indent"></p>
      <p>{{ result }}</p>
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
        indents: 0,
        result: ''
      }
    },
    computed: {
      rows() {
        const rows = [];
        const polynomial = this.polynomial;

        let data = '10111001'; // TODO: Set to this.bits
        let normalized = '';
        let append = '';
        let indents = 0;
        const length = data.length + polynomial.length;

        // First time add as many 0s as there are bits in polynomial
        for (let i = 0; i < polynomial.length; i++) {
          append += '0';
        }

        rows.push({data, append, indent: data.indexOf('1'), indents});

        while (polynomial.length < (length - indents)) {
          append = '';
          for (let i = 0; i < polynomial.length - (data.length - data.indexOf('1')); i++) {
            append += '0';
          }

          // XOR
          normalized = data.substring(data.indexOf('1')) + append;
          data = '';
          for (let i = 0; i < polynomial.length; i++) {
            data += parseInt(polynomial.charAt(i)) ^ parseInt(normalized.charAt(i))
          }

          const indent = data.indexOf('1');

          const row = {data, normalized, append, indent, indents};
          console.log(row)

          indents += indent;

          rows.push(row);
        }

        this.indents = indents;
        this.result = data;

        return rows;
      }
    },
    methods: {
      getIndents(range) {
        let indents = '';
        for (let i = 0; i < range; i++) {
          indents += '&nbsp;';
        }
        return indents;
      },
      last(i) {
        return i < this.rows.length-1;
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

    .append {
      color: $light-gray;
    }

    .polynomial {
      color: $blue;
      border-bottom: 2px solid $light-gray;
      width: max-content;
    }

  }

  .flex {
    display: flex;
  }

</style>
